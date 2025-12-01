/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** subspan.cxx : using c++20 span
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <print>
using std::println;

#include <vector>
using std::vector;
#include <format>
using std::format;
#include <span>
using std:: span;

int main() {

  {
    cout << "SPAN1\n";
    vector v{1,2,3};
    span tail( v.data()+1,2 );
    tail[0] = tail[1] = 0;
    println("{},{},{}",v[0],v[1],v[2]);
    cout << "span1\n";
  }
  {
    cout << "SPAN2\n";
    vector v{1,2,3};
    span data( v.data(),v.size() );
    span tail = data.last(2);
    for ( auto& e : tail )
      e = 0;
    println("{},{},{}",v[0],v[1],v[2]);
    cout << "span2\n";
  }

  return 0;
}
