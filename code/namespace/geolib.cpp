/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** geolib.cxx : geometry library
 ****
 ****************************************************************/

#include <vector>
#include <string>

#include <cmath>
#include "geolib.hpp"

namespace geometry {
  point::point( double x,double y ) {
      xcoord = x; ycoord = y; };
  double point::dx( point other ) {
    return other.xcoord-xcoord; };
  double point::dy( point other ) {
    return other.ycoord-ycoord; };
  segment::segment( point from,point to) 
    : from(from),to(to) {};
  double segment::size() {
    double
      dx = to.dx(from), dy = to.dy(from);
    return std::sqrt( dx*dx + dy*dy );
  };
  template< typename T >
  vector<T>::vector( std::string name,int size )
    : name_(name),std::vector<T>::vector(size) {};
}

template class geometry::vector<float>;
template class geometry::vector<double>;
