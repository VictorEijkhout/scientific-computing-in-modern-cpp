/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** geo.cxx : geometry code in name space, using lib and header file
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <fmt/format.h>
using fmt::format;

// NO: using namespace geometry;

#include <vector>
#include "geolib.hpp" // this contains the geometry namespace
int main() {
  // std vector of geom segments:
  std::vector<geometry::segment> segments;
  segments.push_back( geometry::segment( geometry::point(1,1),geometry::point(4,5) ) );
  std::cout << "First segment has length " << segments[0].size() << '\n';

  std::vector<geometry::vector<float>> vectors;
  vectors.push_back( geometry::vector<float>( "a", 5 ) );
  cout << fmt::format("First vector, \"{}\" has size {}\n",
		      vectors[0].name(),vectors[0].size());

  return 0;
}
