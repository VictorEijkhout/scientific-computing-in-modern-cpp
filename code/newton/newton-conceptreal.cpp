/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** newton-concept.cxx : templating limited to concept float
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
T f(T x);
template<RealType T>
T fprime(T x);

int main() {

  {
    double x{1.};
    while ( true ) {
      auto fx = f<double>(x);
      cout << "f( " << x << " ) = " << fx << '\n';
      if (std::abs(fx)<1.e-10 ) break;
      x = x - fx/fprime<double>(x);
    }
  }
  
  {
    float x{1.};
    while ( true ) {
      auto fx = f<float>(x);
      cout << "f( " << x << " ) = " << fx << '\n';
      if (std::abs(fx)<1.e-5 ) break;
      x = x - fx/fprime<float>(x);
    }
  }  

  return 0;
}

// answer code removed
