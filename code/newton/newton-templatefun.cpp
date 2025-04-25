/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** newton-template.cxx : properly templatized newton library
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
#include <cmath>

#include <complex>
using std::complex;
#include <functional>
using std::function;

// answer code removed
// answer code removed

int main() {

  //codesnippet netwonttmethoduse
  double two = 2.;
  double sqrt2 =
    newton_root<double>
    ( [two] ( double x ) { return x*x - static_cast<double>(two); },
      []    ( double x ) { return static_cast<double>(2) * x; },
      1.
      );
  //codesnippet end
  cout << "Sqrt( 2 ) = " << sqrt2 << '\n';
  
  complex<double> sqrtm2 =
    newton_root<complex<double>>
    ( [two] ( complex<double> x ) { return x*x - static_cast<complex<double>>(-two); },
      []    ( complex<double> x ) { return static_cast<complex<double>>(2) * x; },
      {1.,1.}
      );
  cout << "Sqrt( -2 ) = " << sqrtm2 << '\n';
  
  return 0;
}
