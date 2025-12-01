/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2018-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** range.cxx : range-based iteration over a class
 ****
 ****************************************************************/

#include <iostream>
using std::boolalpha;
using std::cout;

#include <vector>
using std::vector;

#include <algorithm>
using std::any_of;
#include <ranges>

int main() {

  cout << "Filter\n";
  vector<float> numbers
    {1,-2.2,3.3,-5,7.7,-10};
  for ( auto n :
        numbers
        | std::ranges::views::filter
          ( [] (float f) -> bool {
              return f>0; } )
      ) 
    cout << n << " ";
  cout << '\n';
  cout << " .. filter\n";

  cout << "Count\n";
// answer code removed
  cout << " .. count\n";

  return 0;
}
