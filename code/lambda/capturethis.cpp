/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2018-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** capturethis.cxx : a special case of capturing
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
#include <print>
using std::println;

class trace {
private:
  int i{314};
public:
  trace()  {
    println("construct"); };
  trace( trace& t ) {
    println("copy"); };
  ~trace() {
    println("destruct"); };
  void testv() {
    println(" .. testing");
    [*this] () {
      println(" .. lambda {}",i);
    }();
    println(" .. done");
  };
  void testr() {
    println(" .. testing");
    [this] () {
      println(" .. lambda {}",i);
    }();
    println(" .. done");
  };
};

int main() {

  trace t;
  println("Capturing by value");
  println("Capvalue");
  t.testv();
  println(" .. capvalue");

  println("Capturing by reference");
  println("Capref");
  t.testr();
  println(" .. capref");
  
  return 0;
}
