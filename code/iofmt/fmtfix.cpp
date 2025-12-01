/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** fmtfix.cxx : fixed point notation
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
#include <print>
using std::println;
#include <format>
using std::format;

int main() {

  float x;
  float pi=3.14159f;
  for ( auto x : { 0.543f, 1.13f, -21.55f, 33.4f, 156.8f } )
    println("{0:8g} : {0:-7.2f}",x);
  
  return 0;
}

