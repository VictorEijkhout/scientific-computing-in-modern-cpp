/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** overflow.cpp : signed and unsigned overflow
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#include <iomanip>
using std::boolalpha;

#include <print>
using std::print,std::println;

#include <limits>
using std::numeric_limits;

int main() {

  cout << "Dosigned\n";
  {
    using inttype = int32_t;
    inttype twoG
      {static_cast<inttype>(2000'000'000)};
    auto imax = numeric_limits<inttype>::max();
    println("size of int: {}",sizeof(twoG));
    println(" .. with max: {}",imax);
    println("twoG+twoG = {}",twoG+twoG);
#if 0
    cout << "size of int: "
         << sizeof(twoG)
         << "\n with max: " << imax << '\n';
    cout << "twoG+twoG = " << twoG+twoG << '\n';
#endif
  }
  cout << " .. dosigned\n";

  cout << "\nUnsigned\n";
  {
    using inttype = uint32_t;
    inttype fourG
      {static_cast<inttype>(4000'000'000)};
    auto imax = numeric_limits<inttype>::max();
    println("size of int: {}",sizeof(fourG));
    println(" .. with max {}",imax);
    println("fourG+fourG = {}",fourG+fourG);
#if 0
    cout << "size of int: "
         << sizeof(fourG)
         << "\n with max: " << imax << '\n';
    cout << "fourG+fourG = " << fourG+fourG << '\n';
#endif
    // int32_t ifourG = 100'000;
    // cout << "compare: "
    // 	 << ifourG+ifourG << '\n';
  }
  cout << " .. unsigned\n";

  return 0;
}
