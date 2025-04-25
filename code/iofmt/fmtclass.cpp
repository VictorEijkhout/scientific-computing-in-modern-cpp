/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2018-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** fmtclass.cxx : output a class
 ****
 ****************************************************************/

#include <iostream>
using std::cin, std::cout, std::ostream;
#include <format>
using std::format;
#include <print>
using std::println;

#include <string>
using std::string;

class XYclass {
  friend class std::formatter<XYclass>;
private:
  int x; float y;
public:
  XYclass(int x,float y)
    : x(x),y(y) {};
};

//codesnippet fmtclassdef
template<>
class std::formatter<XYclass>{
public:
  constexpr auto parse( std::format_parse_context& ctx ) {
    return ctx.begin(); };
  auto format( const XYclass& z,std::format_context& ctx ) const {
    return std::format_to
      ( ctx.out(),"[ {}, {} ]",z.x,z.y);
  };
};
//codesnippet end

int main() {

  //codesnippet fmtclassuse
  XYclass x(5,6.7);
  println("XYclass: {}",x);
  //codesnippet end

  return 0;
}

