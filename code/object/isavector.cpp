/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction Scientific Programming in C++/Fortran2003
 **** copyright 2023-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** isavector.cxx : object inheriting from vector
 ****
 ****************************************************************/

#include <iostream>
#include <print>
using std::println;
#include <vector>
using namespace std;

//codesnippet inheritfromvector
class witharray : public vector<float> {
  //codesnippet end
public:
  witharray( float n );
};

//codesnippet inheritfromconstructor
witharray::witharray( float n )
  : vector<float>(n) {
};
//codesnippet end

int main() {

  //codesnippet inheritfrommain
  witharray x(5);
  x[ x.size()-1 ] = 3.14;
  println( "{}",x.back() );
  //codesnippet end

  return 0;
}
