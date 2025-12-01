/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2021-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** fxpression4.cxx : expression templates with free functions
 **** sums and scalar products
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <vector>
using std::vector;

class Vector; // forward definition

/*
 * Operators
 */
template< typename ONE,typename TWO >
class sum {
public:
  float operator()( ONE one,TWO two,size_t i ) const {
    return one[i]+two[i]; };
};
template< typename ONE,typename TWO >
class mul {
public:
  float operator()( ONE one,TWO two,size_t i ) const {
    return one[i]*two; };
};

template< typename ONE,typename TWO,typename EVAL >
class VectorExpr {
private:
  const ONE& one; const TWO &two;
public:
  VectorExpr( const ONE& one,const TWO& two )
    : one(one),two(two) {};
  float operator[]( size_t i ) const;
};

/*
 * Operators
 */
template< typename ONE,typename TWO,typename EVAL >
auto operator*( const VectorExpr<ONE,TWO,EVAL>& one, float factor ) {
  return VectorExpr< VectorExpr<ONE,TWO,EVAL>,Vector,
                     mul< VectorExpr<ONE,TWO,EVAL>,float > >
         (one,factor);
};

//  For the next two to be auto, it has to come before any use
template< typename ONE,typename TWO >
auto operator+( const ONE& one, const TWO& other ) {
  return VectorExpr< ONE,TWO,sum<ONE,TWO> >(one,other);
};

template< typename ONE,typename TWO >
auto operator*( const ONE& one, const TWO& other ) {
  return VectorExpr< ONE,TWO,mul<ONE,TWO> >(one,other);
};

class Vector : public vector<float> {
private:
public:
  Vector( size_t n,float v=0.f )
    : vector<float>(n,v) {};
  // evaluate the assignment
  template< typename ONE,typename TWO,typename EVAL >
  void operator=( const VectorExpr<ONE,TWO,EVAL>& ops );
};

template< typename ONE,typename TWO,typename EVAL >
void Vector::operator=( const VectorExpr<ONE,TWO,EVAL>& ops ) {
  for ( size_t i=0; i<size(); ++i )
    (*this)[i] = ops[i];
};



int main() {

  Vector one(10,1),two(10,2),three(10,3),four(10,4);
  Vector five(10);
  five = one+two+three+four;
  cout << "s/b 10\n";
  cout << five.front() << "," << five.back() << '\n';

  four = three*2.5;
  cout << "s/b 7.5\n";
  cout << four.front() << "," << four.back() << '\n';

  cout << "s/b 16\n";
  five = four + three*2.5 + one;
  cout << five.front() << "," << five.back() << '\n';

  // WORK IN PROGRESS
    five = ( one+three ) * 2.5;
  cout << "s/b 10\n";
  cout << five.front() << "," << five.back() << '\n';
  return 0;
}

template< typename ONE,typename TWO,typename EVAL >
float VectorExpr<ONE,TWO,EVAL>::operator[]( size_t i ) const {
  return EVAL()(one,two,i);
};

