/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2018-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** lambdaex.cxx : lambda example
 ****
 ****************************************************************/

#include <functional>
using std::function;

#include <iostream>
using std::cin;
using std::cout;
#include <print>
using std::println;

bool f(int i) { return (i%2==0); };

int main() {
  int count=0;
  auto count_if_f =
    [&count] (int i) {
      if (i%2==0) count++; };
  for ( int i : {1,2,3,4,5} )
    count_if_f(i);
  println("We counted: {}",count);
  return 0;
}
