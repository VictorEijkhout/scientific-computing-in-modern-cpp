/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** funct.cpp : a templated function
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
#include <iomanip>
using std::scientific;
using std::setw;
using std::setprecision;

#include <cmath>

template <typename Real>
void sqrt_diff( Real x ) {
  cout << std::sqrt(x)-1.772 << '\n';
};

int main() {

  sqrt_diff<float>( 3.14f );
  sqrt_diff<double>( 3.14 );

#if 0
  // or equally well
  sqrt_diff( 3.14f );
  sqrt_diff( 3.14 );
#endif
  
  // DOES NOT COMPILE
  //  sqrt_diff( "abc" );
  return 0;
}
