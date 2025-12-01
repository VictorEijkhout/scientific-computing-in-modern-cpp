/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** const.cxx : investigating const behavior
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <vector>
using std::vector;
#include <format>
using std::format;
#include <span>
using std:: span;

void uhoh( const span<float> vs ) {
  vs[0] = 1.;
}

void read( const span<const float> vs ) {
  cout << vs[0];
  // NOT LEGAL:
  // vs[0] = 1.;
}

int main() {

  vector<float> v(20);
  span<float> vsub( v.data(),18 );
  uhoh( vsub );
  read( vsub );

  return 0;
}
