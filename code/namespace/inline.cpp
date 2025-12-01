/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** inline.cxx : inline namespaces
 ****
 ****************************************************************/

#include <iostream>

namespace geometry {
  inline namespace v1 {
   class vector {
   public: float x,y;
   };
  }
  inline namespace v2 {
   class vector {
   public: float x,y,z;
   };
  }
}

using namespace geometry;
int main() {

  {
    using geometry::v1::vector;
    vector p; p.x = 1.f;
  }
  {
    using geometry::v2::vector;
    vector p; p.z = 1.f;
  }

  return 0;
}
