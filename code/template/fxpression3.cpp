/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2021-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** fxpression3.cxx : expression templates with free functions
 **** With templates we can handle arbitrary sums
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <vector>
using std::vector;

class Vector; //forward definition

template< typename ONE,typename TWO >
class VectorSum {
private:
  const ONE& one; const TWO &two;
public:
  VectorSum( const ONE& one,const TWO& two );
  float operator[]( size_t i ) const;
};

class Vector : public vector<float> {
private:
public:
  Vector( size_t n,float v=0.f )
    : vector<float>(n,v) {};
  template< typename ONE,typename TWO >
  void operator=( const VectorSum<ONE,TWO>& ops );
};

//VectorSum<Vector,Vector> operator+( const Vector& one, const Vector& other );
template< typename ONE,typename TWO >
VectorSum<ONE,TWO> operator+( const ONE& one, const TWO& other );
//VectorSum< VectorSum<ONE,TWO>,Vector > operator+( const VectorSum<ONE,TWO>& one, const Vector& add );

int main() {

  Vector one(10,1),two(10,2),three(10,3),four(10,4);
  Vector five(10);
  five = one+two+three+four;
  cout << five.front() << "," << five.back() << '\n';

  return 0;
}

template< typename ONE,typename TWO >
VectorSum<ONE,TWO>::VectorSum( const ONE& one,const TWO& two )
  : one(one),two(two) {};

// the template spec in the return can NOT be omitted
template< typename ONE,typename TWO >
VectorSum<ONE,TWO> operator+( const ONE& one, const TWO& other ) {
  return VectorSum<ONE,TWO>(one,other);
};

// VectorSum<Vector,Vector>
//operator+( const Vector& one,const Vector& other ) {
//  return VectorSum<Vector,Vector>( one,other );
//};

template< typename ONE,typename TWO >
void Vector::operator=( const VectorSum<ONE,TWO>& ops ) {
  for ( size_t i=0; i<size(); ++i )
    (*this)[i] = ops[i];
};

template< typename ONE,typename TWO >
float VectorSum<ONE,TWO>::operator[]( size_t i ) const {
  return one[i]+two[i];
};
