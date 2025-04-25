/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** enumerate.cxx : how close can we get to python enumerate?
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
// to<> not yet in gcc12
// #include <range/v3/all.hpp>
#ifdef RANGES_V3_ALL_HPP
namespace rng = ranges;
#else
namespace rng = std::ranges;
#endif

int main()
{

  {
    //codesnippet enumerateinit
    vector<int> values{2,4,5,7,10};
    for ( size_t i=0; auto v : values )
      cout << "Element " << i++
           << ": " << v << '\n';
    //codesnippet end
  }

  {
    cout << "Enumerate\n";
    //codesnippet enumerateview
    vector<int> values{2,4,5,7,10};
    for ( auto [i,v] : values
            | rng::views::enumerate )
      cout << "Element " << i
           << ": " << v << '\n';
    //codesnippet end
    cout << " .. enumerate\n";
  }
  
  return 0;
}
