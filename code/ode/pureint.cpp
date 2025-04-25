/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2022 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** pureint.cxx : ODE integrator example
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#include <functional>
using std::function;

#include <vector>
using std::vector;

// answer code removed

int main() {

  {
    //codesnippet integratefwd
    double stepsize = .01;
    auto integrate_linear =
      ForwardIntegrator( [] (double x) { return x*x; }, stepsize );
    double int1 = integrate_linear.to(1.);
    //codesnippet end
    double int2 = integrate_linear.to(2.);
    cout << "to 1: " << int1 << ", to 2: " << int2 << '\n';
  }
  {
    double stepsize = .01;
    auto integrate_linear =
      BackwardIntegrator( [] (double x) { return x*x; }, stepsize );
    double int1 = integrate_linear.to(1.);
    double int2 = integrate_linear.to(2.);
    cout << "to 1: " << int1 << ", to 2: " << int2 << '\n';
  }

  return 0;
}
