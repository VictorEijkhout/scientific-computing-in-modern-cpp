/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** unsigned.cxx : the dangers of int and unsigned
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#include <iomanip>
using std::boolalpha;

#include <print>
using std::println,std::print;

#include <limits>

int main() {

  cout << "Limit\n";
  println("max int     : {}",
      std::numeric_limits<int>::max());
  println("min int     : {}",
      std::numeric_limits<int>::min());
  println("max unsigned: {}",
      std::numeric_limits<unsigned int>::max());
  println("min unsigned: {}",
      std::numeric_limits<unsigned int>::min());
  cout << "limit\n";
#if 0
  cout << "max int     : "
       << std::numeric_limits<int>::max()
       << '\n';
  cout << "min int     : "
       << std::numeric_limits<int>::min()
       << '\n';
  cout << "max unsigned: "
       << std::numeric_limits<unsigned int>
            ::max() << '\n';
  cout << "min unsigned: "
       << std::numeric_limits<unsigned int>
            ::min() << '\n';
#endif

  cout << "Cmp\n";
  unsigned int one{1};
  int minusone{-1};
  println("less: {}",(minusone<one));
  cout << "cmp\n";
#if 0
  cout << "less: "
       << boolalpha << (minusone<one)
       << '\n';
#endif

  return 0;
}
