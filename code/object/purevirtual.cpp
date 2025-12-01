/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2019-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** purevirtual.cxx : pure virtual methods and overriding
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <sstream>
#include <cmath>

class Base {
protected:
  int i;
public:
  Base(int i) : i(i) {};
  virtual ~Base() {};
  virtual int thevalue() = 0;
};

class Deriv : public Base {
public:
  Deriv(int i) : Base(i) {};
  virtual int thevalue() override {
    return 25;
  };
};

int main() {

  Deriv five(5);
  cout << five.thevalue() << '\n';
  return 0;
}
