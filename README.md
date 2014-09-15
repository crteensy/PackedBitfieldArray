PackedBitfieldArray
===================

Array-like structure for bitfield-like elements

Sometimes you need an array of elements that have a number of bits that just isn't a multiple of eight.
Here is one.

Element size
-

The elements stored by this array must have an even power of two bits, for example 1, 2, 4, and so on.

Interface
-

The array is created with template arguments for elements size in bits, number of elements, and (optionally) the underlying
data type. By default, the underlying data type is uint8_t, i.e. the maximum number of bits per element is 8.

operator[] is used to access elements as usual.
For a 2-bit element size, accessing array[1] reads or writes bits 2..3 only.

const and non-const forward Iterators are provided for algorithms that rely on an iterator interface. These will be
changed in the future to be random access iterators.

Usage
-

There is a simple example in the /examples folder.
