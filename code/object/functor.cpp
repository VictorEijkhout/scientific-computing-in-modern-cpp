/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2019-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** functor.cxx : parentheses overloading
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <print>
using std::println;

#include <vector>
using std::vector;

#include <algorithm>
using std::for_each;

class IntPrintFunctor {
public:
  void operator()(int x) {
    println("{}",x);
  }
};

// answer code removed

int main() {

  cout << "One" << '\n';
  IntPrintFunctor intprint;
  intprint(5);
  cout << "one" << '\n';

  cout << "Two" << '\n';
  IntPrintTimes printx2(2);
  printx2(1);
  for ( auto i : {5,6,7,8} )
    printx2(i);
  cout << "two" << '\n';
  
  // vector<int> ints{5,6,7,8};
  // for_each
  //   (ints.begin(),ints.end(),
  //    printx2);

  return 0;
}
