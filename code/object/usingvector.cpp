/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction Scientific Programming in C++/Fortran2003
 **** copyright 2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** usingvector.cxx : object privately inheriting from vector
 ****
 ****************************************************************/

#include <iostream>
#include <print>
using std::println;
#include <vector>
using namespace std;

class witharray : private vector<float> {
  using BaseVector = vector<float>;
public:
  using BaseVector::back;
  using BaseVector::size;
  using BaseVector::operator[];
  witharray( float n )
    : vector<float>(n) {
  };
};

int main() {

  witharray x(5);
  x[ x.size()-1 ] = 3.14;
  println( "{}",x.back() );
#if 0
  // This does not compile:
  println( "{}",x.front() );

  /*
     error: constexpr std::vector< ... >::front() is inaccessible within this context
   40 |   println( "{}",x.front() );
      |                 ~~~~~~~^~
  */
#endif 

  return 0;
}
