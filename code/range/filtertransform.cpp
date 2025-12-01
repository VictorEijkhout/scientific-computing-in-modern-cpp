/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** range.cxx : C++20 ranges
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

string vector_as_string( const vector<int> &v ) {
  stringstream s;
  for ( auto e : v )
    s << e << ", ";
  return s.str();
};

int main()
{

  {
    cout << "Zero" << '\n';
    vector<int> v{ 1,2,3,4,5,6 };
    cout
      << "Original data:\n  "
      << vector_as_string(v)
      << '\n';
    auto times_two = v
      | rng::views::transform
          ( [] (int i) {
            return 2*i; } );
    cout << "Times two:\n  ";
    for ( auto c : times_two )
      cout << c << " "; cout << '\n';
    cout << "zero" << '\n';

    cout << "One" << '\n';
    auto over_five = times_two
      | rng::views::filter
          ( [] (int i) {
            return i>5; } );
    cout << "Over five: ";
    for ( auto c : over_five )
      cout << c << " "; cout << '\n';
    cout << "one" << '\n';
  }

  {
    cout << "Second" << '\n';
    vector<int> v{ 1,2,3,4,5,6 };
    cout << "Original data: "
         << "\n  "
         << vector_as_string(v)
         << '\n';
    auto times_two_over_five = v
      | rng::views::transform
          ( [] (int i) {
            return 2*i; } )
      | rng::views::filter
          ( [] (int i) {
            return i>5; } );
    cout << "Times two over five:\n  ";
    for ( auto c : times_two_over_five ) cout << c << " "; cout << '\n';
    cout << "second" << '\n';
  }

  return 0;
}
