/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2018-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** lambdaex.cxx : lambda example
 ****
 ****************************************************************/

#include <functional>
using std::function;

#include <iostream>
using std::cin;
using std::cout;
#include <print>
using std::println;

void apply_to_5
    ( function< void(int) > f ) {
  f(5);
}

int main() {

  cout << "Direct\n";
  cout <<
  [] (float x,float y) -> float {
    return x+y; } ( 1.5, 2.3 )
  << '\n';
  cout << "direct\n";

  cout << "Var\n";
  auto summing = 
    [] (float x,float y) -> float {
    return x+y; };
  cout << summing ( 1.5, 2.3 ) << '\n';
  cout << summing ( 3.7, 5.2 ) << '\n';
  cout << "var\n";
  
  cout << "Pass\n";
  apply_to_5
    ( [] (int i) {
      println("Int: {}",i);
     } );
  cout << "pass\n";
  
  return 0;
}
