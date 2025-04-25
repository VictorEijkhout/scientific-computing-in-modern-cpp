/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** rangepred.cxx : predicates by ranges
 ****
 ****************************************************************/

#include <iostream>
#include <iomanip>
using std::cout, std::boolalpha;
#include <vector>
using std::vector;

#include <ranges>
namespace rng = std::ranges;
#include <algorithm>
using std::ranges::all_of,std::ranges::any_of;

// #include <range/v3/all.hpp>

bool is_prime( int n ) {
  auto divisors =
    rng::views::iota(2)
    | rng::views::take_while( [n] ( auto d ) { return d*d<=n; } );
  return all_of
    ( divisors,
      [n] ( auto d ) { return n%d>0; }
      );
}

int main() {

  // for each n there is an m>n, m even
  //codesnippet allngreaterm
  all_of( rng::views::iota(1,20),
          [] ( auto n ) -> bool {
            return any_of( rng::views::iota(1),
                           [n] ( auto m ) -> bool {
                             if (m>n) {
  //codesnippet end
                               cout << "Found " << m << " greater than " << n << '\n';
                               return true; } else return false;
                           }
                           );
          }
          );

  // for each n there is an m>n, m even
// answer code removed

// answer code removed
// answer code removed
                               cout << "Triplet: " << q << "," << p << "," << r << '\n';
                               return true;
                             } return false;
                           }
                           );
          }
          );
  cout << '\n';  

// answer code removed
                           [p] ( int q ) {
                             // such that p-q = r-p and r prime:
                             int r = 2*p-q;
                             if (is_prime(r)) {
                               cout << "Triplet: " << q << "," << p << "," << r << '\n';
                               return true;
                             } return false;
                           }
                           );
          }
          );
  cout << '\n';  

#if 0
  // for each prime number p>=5
  all_of( rng::views::iota(5)
          | rng::views::filter( [] ( int n ) { return is_prime(n); } ),
          [] ( int p ) {
            // there is a prime q<p
            return any_of( // rng::views::reverse(
                           rng::views::iota(2)
                           | rng::views::filter( [] ( int n ) { return is_prime(n); } )
                           | rng::views::take_while( [p] ( int q ) { return q<p; } )
                           // | ranges::to<vector<int>>() )
                           ,
                           [p] ( int q ) {
                             // such that p-q = r-p and r prime:
                             int r = 2*p-q;
                             if (is_prime(r)) {
                               cout << "Triplet: " << q << "," << p << "," << r << '\n';
                               return true;
                             } return false;
                           }
                           );
          }
          );
#endif

  // unbounded loop. Do that with any_of
#if 0
  all_of( rng::views::iota(1),
          [] ( auto n ) -> bool {
            return any_of( rng::views::iota(1),
                           [n] ( auto m ) -> bool {
                             if (m>n) {
  //codesnippet end
                               cout << "Found " << m << " greater than " << n << '\n';
                               return true; } else return false;
                           }
                           );
          }
          );
#endif
  
  return 0;
}
