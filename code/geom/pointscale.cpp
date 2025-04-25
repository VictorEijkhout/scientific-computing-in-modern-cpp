/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** pointscale.cxx : Point class with private data
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
#include <print>
using std::println;

#include <cmath>
using std::sqrt;

//codesnippet pointscale
class Point {
//codesnippet end
private:
  float x,y;
public:
  Point( float ux,float uy ) {
    x = ux; y = uy;
  };
  //codesnippet pointscale
  Point scale( float a ) {
    Point scaledpoint( x*a, y*a );
    return scaledpoint;
  };
  //codesnippet end
  float dist_to_origin() { return sqrt(x*x + y*y); };
  Point operator*(float factor);
};
//codesnippet end

//codesnippet pointmultop
Point Point::operator*(float f) {
    return Point(f*x,f*y);
};
//codesnippet end

int main() {
  Point p1(1.,2.);
  cout << "Scale2" << '\n';
//codesnippet pointscale
  println("p1 to origin {:.5}",
          p1.dist_to_origin());
  Point p2 = p1.scale(2.);
  println("p2 to origin {:.5}",
          p2.dist_to_origin());
//codesnippet end
  cout << "scale2" << '\n';

  cout << "Mult2" << '\n';
//codesnippet pointmultop
  println("p1 to origin {:.5}",
          p1.dist_to_origin());
  Point scale2r = p1*2.;
  println("scaled right: {}",
          scale2r.dist_to_origin());
  // ILLEGAL Point scale2l = 2.*p1;
//codesnippet end
  cout << "mult2" << '\n';

  return 0;
}

#if 0
//codesnippet pointscaleimpl1
Point Point::scale( float a ) {
  Point scaledpoint =
    Point( x*a, y*a );
  return scaledpoint;
};
//codesnippet end

//codesnippet pointscaleimpl2
Point Point::scale( float a ) {
  return Point( x*a, y*a );
};
//codesnippet end
#endif
