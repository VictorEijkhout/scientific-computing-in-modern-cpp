/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2018-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** bcd.cpp : BCD extraction
 ****
 ****************************************************************/

#include <iostream>
using std::cout;

#include <bit>
#include <bitset>
using std::bitset,std::rotr;

int main() {

  cout << "size of 1 bits: " << sizeof( bitset<1>{} ) << '\n';
  cout << "size of 8 bits: " << sizeof( bitset<8>{} ) << '\n';
  cout << "size of 9 bits: " << sizeof( bitset<9>{} ) << '\n';
  cout << "size of 63 bits: " << sizeof( bitset<63>{} ) << '\n';
  cout << "size of 65 bits: " << sizeof( bitset<65>{} ) << '\n';

  cout << "Decode\n";
  {
// answer code removed
  }

  cout << "Encode\n";
  {
    uint8_t five{5}, seven{7};
    bitset<8> low_byte{seven};
    bitset<8> high_byte = ( bitset<8>{five} )<<4;
    bitset<8> fiftyseven_bits =
      high_byte | low_byte;
    uint8_t fiftyseven_bcd =
      static_cast<uint8_t>(
        fiftyseven_bits.to_ulong() );
    cout << "fiftyseven bits:\n  "
         << fiftyseven_bits << " = "
         << fiftyseven_bcd << '\n';
  }
  cout << " .. encode\n";

  return 0;
}
