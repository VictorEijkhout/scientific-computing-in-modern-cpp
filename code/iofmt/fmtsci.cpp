/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** fmtsci.cxx : scientific notation
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#include <format>
using std::format;

int main() {

  float x;
  //codesnippet fmtsci
  float pi=3.14159f;
  cout <<
    format("|{:+.2e}|{:+.2e}|\n",
           pi,-pi);
  cout <<
    format("|{:-.2e}|{:-.2e}|\n",
           pi,-pi);
  cout <<
    format("|{: .2e}|{: .2e}|\n",
           pi,-pi);
  //codesnippet end
  
  return 0;
}

