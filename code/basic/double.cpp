/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** double.cxx : about the sizes of types
 ****
 ****************************************************************/

#include <iostream>
using std::cout;

#include <limits>
template< typename T >
using limit = std::numeric_limits<T>;

#include <format>
using std::format;
#include <print>
using std::println;

template< typename T >
void print() {
  println("Bytes: {}",sizeof(T));
  println("Bits in mantissa: {}",
	  limit<T>::digits);
  println("Min exp: {}",
	  limit<T>::min_exponent);
  println("Max exp: {}",
	  limit<T>::max_exponent);
#if 0
  println("Bytes: {}",sizeof(T));
  println("Bits in mantissa: {}",limit<T>::digits);
  //println("Radix: {}",limit<T>::radix); // omit
  println("Min exp: {}",limit<T>::min_exponent);
  println("Max exp: {}",limit<T>::max_exponent);
  //println("{}",limit<T>::is_iec559); // omit
#endif
}

int main() {

  cout << "Double:\n";
  print<double>();
  cout << " .. double\n";

  cout << "LongDouble\n";
  print<long double>();
  cout << " .. longdouble\n";

  return 0;
}
