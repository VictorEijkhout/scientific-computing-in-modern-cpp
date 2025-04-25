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

//codesnippet rangecout
#include <ranges>
namespace rng = std::ranges;
#include <algorithm>
//codesnippet end

int main()
{

  int count;
#if 0
  //codesnippet rangedata
  vector<int> v{2,3,4,5,6,7};
  //codesnippet end
#endif

  cout << "Cout\n";
  //codesnippet rangecout
  vector<int> v{2,3,4,5,6,7};
  rng::for_each
    ( v, [] (int i) { cout << i << " "; } );
  //codesnippet end
  cout << '\n';
  cout << " .. cout\n";

  cout << "Count\n";
  //codesnippet rangecount
  count = 0;
  rng::for_each
    ( v,
      [&count] (int i) {
        count += (i<5); }
      );
  cout << "Under five: "
       << count << '\n';
  //codesnippet end
  cout << " .. count\n";

  cout << "Drop\n";
  //codesnippet rangedrop
  count = 0;
  rng::for_each
    ( v | rng::views::drop(1),
      [&count] (int i) {
        count += (i<5); }
      );
  cout << "minus first: "
       << count << '\n';
  //codesnippet end
  cout << " .. drop\n";

  count = 0;
  for ( const auto& e : v | rng::views::drop(1) )
    count += (e<5);
  cout << "same, range looped: " << count << '\n';
  
  cout << "Transformi\n";
  {
    //codesnippet transformi
  vector<float> in{1,2,3,4},out(4);
  std::transform
    ( in.begin(),in.end(), out.begin(),
      [] (float x ) { return std::sqrt(x); } );
  for ( auto x : out ) cout << x << '\n';
    //codesnippet end
  }
  cout << " .. transformi\n";

  cout << "Transformr\n";
  {
    //codesnippet transformr
  vector<float> in{1,2,3,4},out(4);
  for ( auto x : in 
        | rng::views::transform
	  ( [] (float x ) { return std::sqrt(x); } ) )
    cout << x << '\n';
    //codesnippet end
  }
  cout << " .. transformr\n";

  auto enumerate = [cnt=0] (int i) mutable { return pair<int,int>{cnt++,i}; };
  for ( auto [i,e] : v | rng::views::transform( enumerate ) )
    cout << i << ":" << e << '\n';

  return 0;
}
