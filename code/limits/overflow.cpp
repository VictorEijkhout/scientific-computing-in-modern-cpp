/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016=2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** overflow.cxx : illustration of overflow
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <iomanip>
using std::boolalpha;
#include <print>
using std::println;

#include <limits>
#include <cmath>
#include <cfenv>

int main() {

  float bignum = 1.e40;
  float product = bignum*bignum;
  println("product: {}",product);
  println("overflow: {}",
      std::isinf(product));
#if 0
  cout << "product: " << product
       << "\noverflow: " << boolalpha
       << std::isinf(product) << '\n';
#endif

  return 0;
}
