/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** formatfloat.cxx : floating point output
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#include <format>
using std::format;
#include <print>
using std::println;

int main() {

  float x;
  x = 1.234567;
  for (int i=0; i<6; ++i) {
    println
      ("{0:.3e}/{0:7.4}",
       x);
    x *= 10;
  }
  
  return 0;
}

