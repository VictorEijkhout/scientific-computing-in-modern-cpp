/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2020-2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** static.cxx : using static inline 
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#include <random>

int nonrandom_int(int max) {
  std::default_random_engine engine;
  std::uniform_int_distribution<>
    ints(1,max);
  return ints(engine);
};

int realrandom_int(int max) {
  static  std::default_random_engine static_engine;
  std::uniform_int_distribution<>
    ints(1,max);
  return ints(static_engine);
};

int main() {

  // call `nonrandom_int' three times
  cout << "== Nonrandom\n";
  cout << "Three ints: "
       << nonrandom_int(100) << ", "
       << nonrandom_int(100) << ", "
       << nonrandom_int(100) << ".\n";
  cout << "-- nonrandom\n";

  cout << "== Truerandom\n";
  cout << "Three ints: "
       << realrandom_int(100) << ", "
       << realrandom_int(100) << ", "
       << realrandom_int(100) << ".\n";
  cout << "-- truerandom\n";

  return 0;
}
