/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** ptrdouble.cxx : shared pointers to scalar
 ****
 ****************************************************************/

#include <iostream>
using std::cout;

#include <memory>
using std::shared_ptr;
using std::make_shared;

int main() {

  cout << "Double" << '\n';
  {
    // shared pointer to allocated double
    auto array = shared_ptr<double>( new double );
    double *ptr = array.get();
    array.get()[0] = 2.;
    cout << ptr[0] << '\n';
  }
  cout << "double" << '\n';
  cout << "Init" << '\n';
  {
    // shared pointer to initialized double
    auto array = make_shared<double>(50);
    double *ptr = array.get();
    cout << ptr[0] << '\n';
  }
  cout << "init" << '\n';
  
  cout << "Array" << '\n';
  {
    auto array = std::make_unique<double[]>(50);
    double *ptr = array.get();
    array[1] = 2.81;
    cout << ptr[1] << '\n';
  }
  cout << "array" << '\n';
  

  return 0;
}
