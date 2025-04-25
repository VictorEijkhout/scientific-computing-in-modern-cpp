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

  //codesnippet ftempvecadd2
  Vector one(10,1),two(10,2);
  Vector three(10);
  three = one+two;
  cout << three.front() << ","
       << three.back() << '\n';
  //codesnippet end

  return 0;
}

//codesnippet ft2opplus
VectorSum operator+( const Vector& one, const Vector& other ) {
  return VectorSum( one,other );
};
//codesnippet end

//codesnippet ft2assign
void Vector::operator=( const VectorSum& ops ) {
  Vector sum( size() );
  for ( size_t i=0; i<size(); ++i )
    (*this)[i] = ops[i];
};
//codesnippet end

//codesnippet ft2sumconstruct
VectorSum::VectorSum
    ( const Vector& one,const Vector& two )
  : one(one),two(two) {};
//codesnippet end

//codesnippet ft2result
float VectorSum::operator[]( size_t i ) const {
  return one[i]+two[i];
};
//codesnippet end

