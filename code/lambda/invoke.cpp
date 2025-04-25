/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2018-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** invoke.cpp : immediately invoked
 ****
 ****************************************************************/

#include <functional>
using std::function;
//codesnippet end

#include <iostream>
using std::cin;
using std::cout;

#include <vector>
using std::vector;

#include <string>
using std::string;
using std::to_string;

class MyClass {
public:
  MyClass( int i,int j ) {};
  MyClass( string s ) {};
};

int main() {

  bool foo;
#if 0
  //codesnippet invokewrong
  if (foo)
    MyClass x(5,5);
  else
    MyClass x("foo");
  //codesnippet end
#else
  //codesnippet invokeright
  auto x = 
    [foo] () {
      if (foo)
        return MyClass(5,5);
      else
        return MyClass("foo");
    }();
  //codesnippet end
#endif

  return 0;
}
