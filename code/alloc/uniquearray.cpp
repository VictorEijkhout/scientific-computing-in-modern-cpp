/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2014-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** uniquearray.cxx : allocate your own memory through unique ptr
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <format>
using std::format;
#include <print>
using std::println;
#include <memory>
using std::unique_ptr;

//codesnippet uniquear
template< typename scalar >
class container : private unique_ptr<scalar[]> {
  using allocated = unique_ptr<scalar[]>;
public:
  using allocated::operator[];
private:
  int n;
public:
  container( int n )
    : n(n), unique_ptr<scalar[]>( new scalar[n] ) {
    println("Allocating {}",n);
  };
  scalar& at( int i ) {
    if (i<0 or i>=n ) throw( std::out_of_range("") );
    return (*this)[i];
  };
};
  //codesnippet end

int main() {
  cout << "Copy\n";
  {
    container<float> ten(10);
    cout << ten[9] << ten[10];
    // CAN NOT BE COPIED    container<float> dix(ten);
  }
  cout << " .. copy\n";

  return 0;
}
