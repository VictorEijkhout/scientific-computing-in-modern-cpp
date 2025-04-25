/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** concept.cpp : concepts for limiting templates
 ****
 ****************************************************************/

#include <iostream>
using std::cin, std::cout;
#include <iomanip>
using std::scientific, std::setw, std::setprecision;

//codesnippet conceptint
#include <type_traits>
template<typename T>
concept Integral = std::is_integral_v<T>;
//codesnippet end

//codesnippet conceptgcd0
template <typename T>
requires Integral<T>
T gcd0( T a, T b ) {
  if (b==0) return a;
  else return gcd0(b,a%b);
}
//codesnippet end

//codesnippet conceptgcd1
template <Integral T>
T gcd1( T a, T b ) {
  if (b==0) return a;
  else return gcd1(b,a%b);
}
//codesnippet end

//codesnippet conceptgcd2
Integral auto gcd
    ( Integral auto a, Integral auto b ) {
  if (b==0) return a;
  else return gcd(b,a%b);
}
//codesnippet end

// this comes from ChatGPT and seems wrong
template<typename T>
concept PositiveIntegral = requires {
    { std::is_integral_v<T> && (T{1} > T{0}) }
      -> std::same_as<bool>;
};

// template<typename T>
// concept Integral = std::is_integral<T>::value;

PositiveIntegral auto positive_gcd
    ( PositiveIntegral auto a, PositiveIntegral auto b ) {
  if (b==0) return a;
  else return positive_gcd(b,a%b);
}

int main() {

  //codesnippet conceptgcdcall
  int i=27,j=30;
  cout << "gcd(27,30)="
       << gcd(i,j) << '\n';
  long ii=27'000'000'000,
    jj=30'000'000'000;
  cout << "gcd(27G,30G)="
       << gcd(ii,jj) << '\n';
  // WRONG: DOES NOT COMPILE
  // gcd(27.1,30.2);
  //codesnippet end

  positive_gcd(-27,30);

  return 0;
}

