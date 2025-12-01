/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** range.cxx : C++20 ranges
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <vector>
using std::vector;
#include <tuple>
using std::pair;
#include <cmath>

#include <ranges>
namespace rng = std::ranges;
#include <algorithm>

int main()
{

  int count;
#if 0
  vector<int> v{2,3,4,5,6,7};
#endif

  cout << "Cout\n";
  vector<int> v{2,3,4,5,6,7};
  rng::for_each
    ( v, [] (int i) { cout << i << " "; } );
  cout << '\n';
  cout << " .. cout\n";

  cout << "Count\n";
  count = 0;
  rng::for_each
    ( v,
      [&count] (int i) {
        count += (i<5); }
      );
  cout << "Under five: "
       << count << '\n';
  cout << " .. count\n";

  cout << "Drop\n";
  count = 0;
  rng::for_each
    ( v | rng::views::drop(1),
      [&count] (int i) {
        count += (i<5); }
      );
  cout << "minus first: "
       << count << '\n';
  cout << " .. drop\n";

  count = 0;
  for ( const auto& e : v | rng::views::drop(1) )
    count += (e<5);
  cout << "same, range looped: " << count << '\n';
  
  cout << "Transformi\n";
  {
  vector<float> in{1,2,3,4},out(4);
  std::transform
    ( in.begin(),in.end(), out.begin(),
      [] (float x ) { return std::sqrt(x); } );
  for ( auto x : out ) cout << x << '\n';
  }
  cout << " .. transformi\n";

  cout << "Transformr\n";
  {
  vector<float> in{1,2,3,4},out(4);
  for ( auto x : in 
        | rng::views::transform
	  ( [] (float x ) { return std::sqrt(x); } ) )
    cout << x << '\n';
  }
  cout << " .. transformr\n";

  auto enumerate = [cnt=0] (int i) mutable { return pair<int,int>{cnt++,i}; };
  for ( auto [i,e] : v | rng::views::transform( enumerate ) )
    cout << i << ":" << e << '\n';

  return 0;
}
