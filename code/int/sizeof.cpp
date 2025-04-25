/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** sizeof.cxx : size of fixed width int types
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#include <iomanip>
using std::boolalpha;

#include <print>
using std::print,std::println;

#include <cstdint>

int main() {

  //codesnippet sizeoffixed
  int8_t i8;
  uint8_t u8;
  int16_t i16;
  uint16_t u16;
  println("{}, {}, {}, {}",
	  sizeof(i8),
	  sizeof(u8),
	  sizeof(i16),
	  sizeof(u16)
	  );
  //codesnippet end
#if 0
  cout << sizeof(i8)
       << ", " << sizeof(u8)
       << ", " << sizeof(i16)
       << ", " << sizeof(u16)
       << '\n';
#endif

  return 0;
}
