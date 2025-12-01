/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** lambda-complex.cxx : newton scalar example
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
};

template<typename T>
T newton_root( function< T(T) > f, T h,T init ) {
  cout << "gradient-free newton with h=" << h << '\n';
  return newton_root<T>( f, [f,h] (T x) -> T { return (f(x+h)-f(x))/h; },init );
};

int main() {

  cout << "sqrt 2 = " <<
       newton_root<double>
            ( [] (double x) { return x*x-2; }, [] (double x) { return x*2; },
            /* init: */ .5 )
       << '\n';

  cout << "sqrt 2 = " <<
       newton_root<double>
            ( [] (double x) { return x*x-2; }, .001,.5 )
       << '\n';

  cout << "sqrt -2 = " <<
    newton_root<complex<double>>
    ( // objective function
      [] (complex<double> x) -> complex<double> {
          return x*x + static_cast<complex<double>>(2); },
      // derivative
      [] (complex<double> x) -> complex<double> {
          return x * static_cast<complex<double>>(2); },
      // initial value
      complex<double>{.1,.1}
      )
       << '\n';

  cout << "sqrt -2 = " <<
       newton_root<complex<double>>
            ( [] (complex<double> x) { return x*x+static_cast<complex<double>>(2); },
              complex<double>{.001,.001},
              complex<double>{.1,.1}
              )
       << '\n';

  
  return 0;
}
