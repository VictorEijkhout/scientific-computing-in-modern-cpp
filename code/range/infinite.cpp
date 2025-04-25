/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** infinite.cxx : unlimited iota
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <sstream>
using std::stringstream;
#include <string>
using std::string;

#include <vector>
using std::vector;

#include <ranges>
//#include <range/v3/all.hpp>
#ifdef RANGES_V3_ALL_HPP
namespace rng = ranges;
#else
namespace rng = std::ranges;
#endif

#include <fmt/format.h>

int main()
{

  //codesnippet infeven
  auto even_numbers =
    rng::views::iota(0)
    | rng::views::filter
        ( [] ( auto n ) { return n%2==0; } );
  for ( auto n : even_numbers
          | rng::views::take(10) )
    cout << n << '\n';
  //codesnippet end

  return 0;
}
