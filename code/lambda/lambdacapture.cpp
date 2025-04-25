/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2018-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** lambdacapture.cxx : exploring the capture
 ****
 ****************************************************************/

#include <functional>
using std::function;

#include <iostream>
using std::cin;
using std::cout;
#include <print>
using std::println;

#include <vector>
using std::vector;

#include <string>
using std::string;
using std::to_string;

int main() {

  cout << "Value\n";
  //codesnippet lambdavalue
  int n;
  cin >> n;
  auto increment_by_n = 
    [n] ( int input ) -> int {
      return input+n;
  };
  println("{}",increment_by_n (5));
  println("{}",increment_by_n (12));
  println("{}",increment_by_n (25));
  //codesnippet end
  cout << "value\n";

  int one=1;
  cout << "Constant\n";
  {
    //codesnippet lambdaconstant
    int inc;
    cin >> inc;
    auto increment =
      [inc] ( int input ) -> int {
        return input+inc;
      };
    println("increment by: {}",inc);
    println("1 -> {}",increment(1));
    inc = 2*inc;
    println("1 -> {}",increment(1));
    //codesnippet end
  }
  cout << "constant\n";

  cout << "Mutate\n";
  //codesnippet lambdautate
  [one] ( int input ) -> void {
    // WRONG: does not compile:
    // one++;
    println("{}",input+one);
  } (5);
  //codesnippet end
  cout << "mutate\n";

  cout << "Reference\n";
  //codesnippet lambdareference
  int stride = 1;
  auto more_and_more = 
    [&stride] ( int input ) -> void {
      println("{} => {}",input,input+stride);
      ++stride;
  };
  more_and_more(5);
  more_and_more(6);
  more_and_more(7);
  more_and_more(8);
  more_and_more(9);
  println("stride is now: {}",stride);
  //codesnippet end
  cout << "reference\n";

  // capture everything by value
  auto cap_const =
    [=] ( float x ) -> float {
      return x; //whatever
    };
  // capture everything by reference
  auto cap_ref =
    [&] ( float x ) -> float {
      return x; //whatever
    };

  return 0;
}
