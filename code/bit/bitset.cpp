/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2023-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** bitset.cxx : bitwise operators
 ****
 **** LOOKS LIKE PRNT DOES NOT WORK ON BITSET
 ****
 ****************************************************************/

#include <iostream>
using std::cin,  std::cout;
#include <print>
using std::println;

#include <bitset>
using std::bitset;

int main() {

  //codesnippet bitsetandor
  bitset<8> xb(6);
  bitset<8> yb(3);
  cout << "6|3 = " << (xb|yb)
       << " = " << xory << '\n';
  auto xandy = (xb&yb).to_ulong();
  cout << "6&3 = " << (xb&yb)
       << " = " << xandy << '\n';
  //codesnippet end
#if 0
  auto xory = (xb|yb).to_ulong();
  println("6|3 = {} = {}",
          (xb|yb),xory );

  auto xandy = (xb&yb).to_ulong();
  println("6&3 = {} = {}",
          (xb&yb),xandy);
#endif
  
  return 0;
}
