#ifndef SFDD_PACKEDBITFIELDARRAY_H
#define SFDD_PACKEDBITFIELDARRAY_H

#include <array>
#include <cstdint>

template<size_t Bits, size_t Elements, typename V = uint8_t>
class PackedBitfieldArray
{
  // array type for packable bitfields-kinda-types

  public:
    typedef V value_type;

    static constexpr size_t value_bitwidth = 8*sizeof(value_type);
    static_assert(Bits <= value_bitwidth, "Bit size must not be greater than the underlying storage type's bit size");
    static_assert(value_bitwidth % Bits == 0, "Cannot pack this : (value_bitwidth % Bits per element) != 0");

    static constexpr value_type arg_mask = (1<< Bits)-1;
    // number of underlying storage elements
    static constexpr size_t value_size = (Bits*Elements+(value_bitwidth-1))/value_bitwidth;

    class proxy
    {
      public:
        proxy(value_type& data, size_t offset) : data_(data), offset_(offset) {}

        proxy& operator=(value_type value)
        {
          value_type orVal = ((value & arg_mask) << offset_);
          data_ = (data_ & ~(arg_mask << offset_)) | orVal;
          return *this;
        }

        operator value_type() const
        {
          return (data_ & (arg_mask << offset_)) >> offset_;
        }

      private:
        value_type& data_;
        size_t offset_;
    };

    class const_proxy
    {
      public:
        const_proxy(value_type& data, size_t offset) : data_(data), offset_(offset) {}

        operator value_type() const
        {
          return (data_ & (arg_mask << offset_)) >> offset_;
        }

      private:
        const value_type& data_;
        size_t offset_;
    };

    value_type* data() {return data_.data();}
    const value_type* data() const {return data_.data();}

    proxy operator[](size_t i)
    {
      size_t i_ = i*Bits/value_bitwidth;
      uint8_t offset = i * Bits % value_bitwidth;
      return proxy(data()[i_], offset);
    }

    class iterator : public std::iterator<std::forward_iterator_tag, proxy>
    {
      public:
        iterator(value_type* data, size_t i)
        {
          size_t i_ = i*Bits/value_bitwidth;
          offset_ = i * Bits % value_bitwidth;
          data_ = &data[i_];
        }

        proxy operator*() const {return proxy(*data_, offset_);}

        iterator& operator++()
        {
          offset_ += Bits;
          if (offset_ == value_bitwidth)
          {
            offset_ = 0;
            data_++;
          }
          return *this;
        }

        bool operator==(const iterator& rhs)
        {
          return ((data_ == rhs.data_) && (offset_ == rhs.offset_));
        }

        bool operator!=(const iterator& rhs) {return !(operator==(rhs));}
      private:
        value_type* data_;
        size_t offset_;

    };

    iterator begin()
    {
      return iterator(data_.data(), 0);
    }

    iterator end()
    {
      return iterator(&data_.data()[value_size], 0); // WRONG
    }

  private:
  std::array<value_type, value_size> data_;
};


#endif // SFDD_PACKEDBITFIELDARRAY_H

