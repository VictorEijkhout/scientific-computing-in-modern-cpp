/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** pointfun.cxx : class with method
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#include <sstream>
using std::stringstream;
#include <string>
using std::string;
#include <format>
using std::format;

#include <cmath>
using std::sqrt;

class Point {
private:
  float x,y;
public:
  Point( float xx,float yy )
    : x(xx),y(yy) {};
  float length() {
    return sqrt(x*x + y*y); };
  float angle() {
    return 0.; /* something trig */;
  };
  string as_string() {
    stringstream ss;
    ss << "(" << x << "," << y << ")";
    return ss.str();
  };
  string as_fmt_string() {
    auto ss = format("({},{})",x,y);
    return ss;
  };
};

std::ostream& operator<<
(std::ostream &out,Point &p) {
  out << p.as_string(); return out;
};

int main() {
  cout << "Simple\n";
  {
    Point p1(1.,2.);
    cout << "p1 has length "
         << p1.length() << "\n";
  }
  cout << "simple\n";
  
  cout << "Cout\n";
  {
    Point p1(1.,2.);
    cout << "p1 " << p1
         << " has length "
         << p1.length() << "\n";
  }
  cout << "cout\n";

  return 0;
}
