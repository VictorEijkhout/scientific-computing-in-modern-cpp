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

class witharray : public vector<float> {
public:
  witharray( float n );
};

witharray::witharray( float n )
  : vector<float>(n) {
};

int main() {

  witharray x(5);
  x[ x.size()-1 ] = 3.14;
  println( "{}",x.back() );

  return 0;
}
