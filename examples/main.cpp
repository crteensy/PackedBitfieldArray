/**
  Compile in the examples folder with:

  > g++ -Wall -std=c++0x -Os -o main main.cpp

  Then execute and see the test results
**/

#include <algorithm>
#include <bitset>
#include <iostream>

#include "../packedBitfieldArray.h"

int main()
{
  static const size_t bits = 2;
  static const size_t n = 8;
  typedef PackedBitfieldArray<bits, n, uint8_t> PackedBitfield;
  PackedBitfield a;

  using namespace std;

  cout << "bits = " << bits << ", n = " << n << ", [a] = " << sizeof(a) << "\n";
  cout << "a.arg_mask = 0b" << std::bitset<8*sizeof(PackedBitfield::value_type)>(a.arg_mask) << "\n\n";

  /* Fill with indices */
  for (size_t i = 0; i < n; i++)
  {
    a[i] = i;
  }

  cout << "\nfor loop, C-like element access:\n";
  for (size_t i = 0; i < n; i++)
  {
    cout << "a[" << i << "] = " << (int)a[i] << "\n";
  }

  cout << "\nfor loop with iterators:\n";
  for (auto it = a.begin(); it != a.end(); ++it)
  {
    cout << "a[...] = " << (int)*it << " (0b" << std::bitset<8*sizeof(PackedBitfield::value_type)>(*it) << ")\n";
  }

  cout << "\nfor_each with a lambda:\n";
  std::for_each(a.begin(), a.end(), [](const PackedBitfield::proxy pr) {cout << "a[...] = " << (int)pr << " (0b" << std::bitset<8*sizeof(PackedBitfield::value_type)>(pr) << ")\n";});

  cout << "\nunderlying data dump:\n";
  for (size_t i = 0; i < a.value_size; i++)
  {
    cout << "a[" << i << "_] = " << (int)a.data()[i] << " (0b" << std::bitset<8*sizeof(PackedBitfield::value_type)>(a.data()[i]) << ")\n";
  }

  return 0;
}
