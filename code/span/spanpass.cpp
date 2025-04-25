/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** spanpass.cxx : using c++20 span
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <print>
using std::println;

#include <vector>
using std::vector;
#include <format>
using std::format;
#include <span>
using std:: span;

//codesnippet spanpass
void f( span<int> s ) { 
  println("{}",s[0]);
}
int main() {
  std::array<int,1> a{1};
  f( a );
  int b[2]{2,2};
  f( b );
  vector<int> c(5,3);
  f( c );
//codesnippet end

  return 0;
}
