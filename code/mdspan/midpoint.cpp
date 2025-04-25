/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2019-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** midpoint.cxx : illustrating indexing
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#include <vector>
using std::vector;

#include <ranges>
//#include <range/v3/all.hpp>
#ifdef RANGES_V3_ALL_HPP
namespace rng = ranges;
#else
namespace rng = std::ranges;
#endif

// #include <mdspan>

#include "mdspan/mdspan.hpp"
namespace md = Kokkos;
namespace KokkosEx = MDSPAN_IMPL_STANDARD_NAMESPACE::MDSPAN_IMPL_PROPOSED_NAMESPACE;
namespace mdx = KokkosEx;

int main() {

  //codesnippet mdspan4dmid
  vector<float> ar10203040(10*20*30*40);
  auto brick10203040 =
    md::mdspan< float,
                md::extents<size_t,10,20,30,40> >
                    ( ar10203040.data() );
  auto midpoint = brick10203040[5,10,15,20];
  //codesnippet end

  return 0;
}
