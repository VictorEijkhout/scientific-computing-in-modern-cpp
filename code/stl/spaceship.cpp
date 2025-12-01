/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2023-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** spaceship.cxx : example
 ****
 ****************************************************************/

#include <iostream>
#include <iomanip>
using std::cin, std::cout, std::endl, std::boolalpha;

#include <format>
using std::format;
#include <print>
using std::println;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <array>
using std::array,std::to_array;

class Record {
private:
  static inline int nrecords{0};
  int myrecord{-1};
  string name;
public:
  Record( string name )
    : name(name) { myrecord = nrecords++; };
  std::strong_ordering operator<=>( const Record& other ) const {
    return myrecord<=>other.myrecord;
  };
  bool operator==( const Record& other) const {
    return myrecord==other.myrecord;
  };
};

#include <compare>
template<typename T>
class Coordinate {
private:
  array<T,2> components;
public:
  Coordinate( T x,T y )
    : components( to_array({x,y} ) ) {};
  std::partial_ordering operator<=>( const Coordinate& other ) const {
    std::strong_ordering c = components[0] <=> other.components[0];
    for (int i = 1; i <components.size(); ++i) {
      if ((components[i] <=> other.components[i]) != c)
        return std::partial_ordering::unordered;
    }
    return c;
  };
  bool operator==( const Coordinate& other ) const {
    for ( int ic=0; ic<components.size(); ++ic ) 
      if (components[ic]!=other.components[ic])
	return false;
    return true;
  };
};

int main() {

  cout << "Record\n";
  // WARNING some of these comparisons seem ambiguous
  Record alice("alice"), bob("bob");
  println("expect  t f  t t  f f");
  println( "{}", (alice==alice) );
  println( "{}", (alice==bob) );
  println( "{}", (alice<=bob) );
  println( "{}", (alice<bob) );
  println( "{}", (alice>=bob) );
  println( "{}", (alice>bob) );
  cout << " .. record\n";
  
  cout << "Partial\n";
  Coordinate<int> p12(1,2),p24(2,4),p31(3,1);
  println("expect t t f");
  println("{}",(p12==p12));
  println("{}",(p12<p24));
  println("{}",
      (p12<p31 or p12>p31 or p12==p31));
  cout << " .. partial\n";

  return 0;
}
