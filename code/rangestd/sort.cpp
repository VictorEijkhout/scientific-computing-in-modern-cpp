/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** sort.cxx : sorting
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
namespace rng = std::ranges;
// for sort:
#include <algorithm>

string vector_as_string( const vector<int> &v ) {
  stringstream s;
  for ( auto e : v )
    s << e << ", ";
  return s.str();
};

int main()
{

  cout << "ItSort\n";
  vector<int> v{3,1,2,4,5,7,9,11,12,8,10};
  cout << "Original vector: "
       << vector_as_string(v) << '\n';

  auto v_std(v);
  std::sort( v_std.begin(),v_std.begin()+5 );
  cout << "Five elements sorts: "
       << vector_as_string(v_std) << '\n';
  cout << "itsort\n";

  auto v_range(v);
  rng::sort(rng::views::drop(v_range, 5));

  {
    cout << "RngSort\n";
    vector<int> v{3,1,2};
    rng::sort(v);
    for ( auto e : v )
      cout << e << '\n';
    cout << " .. rngsort\n";
  }

  return 0;
}
