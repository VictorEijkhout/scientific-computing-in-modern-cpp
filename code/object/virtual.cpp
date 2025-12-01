/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2019-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** virtual.cpp : virtual methods and overriding
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <print>
using std::println;
#include <sstream>
#include <cmath>

class Base {
protected:
  int i;
public:
  Base(int i) : i(i) {};
  virtual int thevalue() { return i; };
};

class Deriv : public Base {
public:
  Deriv(int i) : Base(i) {};
  virtual int thevalue() override {
    int ivalue = Base::thevalue();
    return ivalue*ivalue;
  };
};

int main() {

  Base fiveb(5);
  println("{}",fiveb.thevalue());
  Deriv fived(5);
  println("{}",fived.thevalue());

  return 0;
}
