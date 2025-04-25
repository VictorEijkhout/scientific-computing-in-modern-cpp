/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2018-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** fmtbasic.cxx : simplest example
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
using std::ostream;
#include <format>
using std::format;
#include <print>
using std::println;

#include <string>
using std::string;

int main() {

  //codesnippet fmtbasic
  println("{}",2);
  string hello_string = format
    ("{} {}!","Hello","world");
  cout << hello_string << '\n';
  println
    ("{0}, {0} {1}!",
     "Hello","world");
  //codesnippet end

  return 0;
}

