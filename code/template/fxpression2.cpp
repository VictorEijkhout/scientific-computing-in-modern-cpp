/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2021-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** fxpression2.cxx : expression templates with free functions
 **** Untemplated: this can only handle sum of 2 terms.
 ****
 ****************************************************************/

#include <iostream>
using std::cout;

#include "fxpression2.hpp"

int main() {

  Vector one(10,1),two(10,2);
  Vector three(10);
  three = one+two;
  cout << three.front() << ","
       << three.back() << '\n';

  return 0;
}

VectorSum operator+( const Vector& one, const Vector& other ) {
  return VectorSum( one,other );
};

void Vector::operator=( const VectorSum& ops ) {
  Vector sum( size() );
  for ( size_t i=0; i<size(); ++i )
    (*this)[i] = ops[i];
};

VectorSum::VectorSum
    ( const Vector& one,const Vector& two )
  : one(one),two(two) {};

float VectorSum::operator[]( size_t i ) const {
  return one[i]+two[i];
};

