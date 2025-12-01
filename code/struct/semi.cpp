/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** semi.cxx : semiconductor
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

struct semiconductor {
  double p; double n; double phi;
};

semiconductor model() {
  double p = 1.5;
  double n = 2.5;
  double phi = 3.5;
  return {.p=p, .n=n, .phi=phi};
};

int main() {

  auto m = model();

  return 0;
}

