/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2019-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** expected.cpp : expected results
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#include <cmath>

#include <expected>
using std::expected;

//codesnippet expectedconstruct
std::expected<double,string> 
square_root( double x ) {
  if (x<0)
    return std::unexpected("negative");
  else if (x<limits<double>::min())
    return std::unexpected("underflow");
  else {
    auto result = sqrt(x);
    return result;
  }
}
//codesnippet end

int main() {

  //codesnippet expectedmain
  auto root = square_root(x);
  if (x)
    cout << "Root=" << root.value() << '\n';
  else if (root.error()==/* et cetera */ )
    /* handle the problem */
  //codesnippet end
  
  return 0;
}

