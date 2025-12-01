/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** pointx.cxx : access through arrow
 ****
 ****************************************************************/

#include <iostream>
using std::cout;

#include <print>
using std::println;

#include <memory>
using std::make_shared;


class HasX {
private:
  double x;
public:
  HasX( double x) : x(x) {};
  auto value() { return x; };
  void set(double xx) {
    x = xx; };
};

int main() {

  {
    HasX xobj(5);
    println("{}",xobj.value());
    xobj.set(6);
    println("{}",xobj.value());
  }

  {
    cout << "Pointuse\n";
    HasX xobj(5);
    println("{}",xobj.value());
    xobj.set(6);
    println("{}",xobj.value());

    auto xptr = make_shared<HasX>(5);
    println("{}",xptr->value());
    xptr->set(6);
    println("{}",xptr->value());
    cout << " .. pointuse\n";
  }

  {
    cout << "Twopoint\n";
    auto xptr = make_shared<HasX>(5);
    auto yptr = xptr;
    println("{}",xptr->value());
    yptr->set(6);
    println("{}",xptr->value());
    cout << " .. twopoint\n";
  }

  return 0;
}
