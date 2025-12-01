/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** constchange.cxx : attempt to change const => compiler error
 ****
 ****************************************************************/

void f(const int i) {
  ++i; // COMPILER ERROR!
}

int main() {

  return 0;
}
