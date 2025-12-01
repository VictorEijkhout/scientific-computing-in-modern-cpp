/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** newton-conceptint.cxx : concepts wrongly applied
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
#include <cmath>

#include <complex>
using std::complex;

#include <concepts>

template<typename T>
concept RealType = std::is_floating_point_v<T>;

template<RealType T>
T f(T x) { return x*x - static_cast<T>(2); };
template<RealType T>
T fprime(T x) { return static_cast<T>(2) * x; };

int main() {

  // WRONG: this should not compile
  int i{5};
  while ( true ) {
    auto fi = f<int>(i);
    cout << "f( " << i << " ) = " << fi << '\n';
    if (std::abs(fi)<1.e-10 ) break;
    i = i - fi/fprime<int>(i);
  }
  
  return 0;
}
