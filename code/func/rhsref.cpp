/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2018-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** rhsref.cxx : result of an expression can not be reference
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <print>
using std::println;

class myclass {
private:
  int stored{0};
public:
  myclass(int i) : stored(i) {};
  int &data() { return stored; };
};

int main() {

  myclass obj(5);
  println("object data: {}",obj.data());
  int dcopy = obj.data();
  ++dcopy;
  println("object data: {}",obj.data());
  int &dref = obj.data();
  ++dref;
  println("object data: {}",obj.data());
  auto dauto = obj.data();
  ++dauto;
  println("object data: {}",obj.data());
  auto &aref = obj.data();
  ++aref;
  println("object data: {}",obj.data());

  return 0;
}
