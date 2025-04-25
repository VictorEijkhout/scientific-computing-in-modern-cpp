/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2019-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** logic.cpp : logic operator overloading
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <print>
using std::println;

#include <algorithm>

//codesnippet fuzzybitclass
class FuzzyBit {
private:
  float value_; // between 0 and 1
public:
  FuzzyBit( float value) : value_(value) {};
  /* ... */
  //codesnippet end
  //codesnippet fuzzybitcode
  FuzzyBit operator&&( FuzzyBit other ) {
    return FuzzyBit
      ( std::min(value_,other.value_) );
  };
  FuzzyBit operator||( FuzzyBit other ) {
    return FuzzyBit
      ( std::max(value_,other.value_) );
  };
  operator bool() const {
    return value_>=.5f; };
  //codesnippet end
};
  
int main() {

  //codesnippet fuzzybitmain
  FuzzyBit yes{1},no{0};
  FuzzyBit confirm = (yes or no );

  if ( confirm )
    println("Yes");
  else
    println("No");
  //codesnippet end
  
  return 0;
}
//codesnippet end

