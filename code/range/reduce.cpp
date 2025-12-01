/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2019-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** reduce.cxx : use of reductions in ranges
 ****
 ****************************************************************/


#include <iostream>
using std::cin;
using std::cout;

#include <vector>
using std::vector;

// #include <ranges>
// we need accumulate
#include <range/v3/all.hpp>
#ifdef RANGES_V3_ALL_HPP
namespace rng = ranges;
#else
namespace rng = std::ranges;
#endif

#include <numeric>
using std::multiplies;

class x {
public:
  int i,j;
  x() {};
  x(int i,int j) : i(i),j(j) {};
};

int main() {

  {
    cout << "Accumulate .." << '\n';
    vector<int> v{1,3,5,7};
    auto first = v.begin();
    auto last  = v.end();
    auto sum = rng::accumulate(first,last,0);
    cout << "sum: " << sum << '\n';
    cout << ".. accumulate" << '\n';
  }

  {
    cout << "Product .." << '\n';
    vector<int> v{1,3,5,7};
    auto product =
      rng::accumulate
        (v,2,multiplies<>());
    cout << "multiplied: " << product << '\n';
    cout << ".. product" << '\n';
  }

  {
    cout << "Class .. \n";
    std::vector<x> xs(5);
    auto xxx = 
      std::accumulate
      ( xs.begin(),xs.end(),0,
	[] ( int init,x x1 ) -> int { return x1.i+init; }
	);
    cout << ".. class\n";
  }
  
  return 0;
}

