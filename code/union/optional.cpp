/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2019-2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** optional.cpp : optional results
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#include <cmath>

#include <optional>
using std::optional;

class WithInt {
public:
  WithInt( int i ) {};
  void foo() {};
};

int main() {

  cout << "BadValue\n";
  optional<float> maybe_number = {};
  try {
    cout << maybe_number.value() << '\n';
  } catch (std::bad_optional_access) {
    cout << "failed to get value\n";
  }
  cout << "badvalue\n";

  optional<WithInt> maybe;
  { maybe.emplace(5); }
  cout << maybe.has_value() << '\n';
  maybe.value().foo();
  
  return 0;
}

