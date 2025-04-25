/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** newton1.cxx : newton scalar example
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
#include <cmath>

#include <functional>
using std::function;

// answer code removed
  double x{1.};
  while ( true ) {
    auto fx = f(x);
    // cout << "f( " << x << " ) = " << fx << '\n';
    if (std::abs(fx)<1.e-10 ) break;
    x = x - fx/fprime(x);
  }
  return x;
};

// answer code removed

int main() {

  cout << "sqrt 2 = " <<
       newton_root( [] (double x) { return x*x-2; }, [] (double x) { return 2*x; } )
       << '\n';

// answer code removed
// answer code removed
// answer code removed
  }

  for ( auto h : { .01, .0001, .0000001, 1.e-12, 1., 3. } )
    newton_root( [] (double x) {return x*x-2; }, h );
  
  return 0;
}
