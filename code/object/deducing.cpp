/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** deducing.cxx : deducing this in C++23
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#ifndef __cpp_explicit_this_parameter
#warning "Your compiler does not support deducing this yet"
#endif

class HasNumber {
private:
  float x_;
public:
  //  float& x() { return x_; };
  // const float& x() const { return x_; };
  // why?
  //  auto x() && { return x_; };
#ifndef __cpp_explicit_this_parameter
  auto& x() & { return x_; };
  auto& x() const & { return x_; };
#else
  template<typename Self>
  auto& x(this Self&& self) { 
    return self.x_ ;
    };
    // return std::forward<Self>(self).x_; 
#endif
};

int main() {

  HasNumber x;
  x.x() = 5;
  cout << x.x() << '\n';
  return 0;
}

// https://godbolt.org/z/dfsE3nfY8
