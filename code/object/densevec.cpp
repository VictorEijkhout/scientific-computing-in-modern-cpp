/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** densevec.cxx : implementing a dense vector on virtual vector base
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <print>
using std::println;

#include <vector>
using std::vector;

#include "virtualvec.hpp"

//codesnippet virtfuncdense
class DenseVector : VirtualVector {
private:
  vector<float> values;
public:
  DenseVector( int size ) {
    values = vector<float>(size,0);
  };
//codesnippet end
//codesnippet virtfuncdensemethod
  void setlinear( float v ) {
    for (int i=0; i<values.size(); ++i)
      values[i] = i*v;
  };
  float operator[](int i) {
    return values[i];
  };
};
//codesnippet end

int main() {
  //codesnippet virtfuncmain
  DenseVector v(5);
  v.setlinear(7.2);
  println("{:.3}",v[3]);
  //codesnippet end
  return 0;
}
