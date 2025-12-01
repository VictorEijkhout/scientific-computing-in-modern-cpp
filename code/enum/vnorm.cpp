/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2018-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** enum.cxx : examples of enums
 ****
 ****************************************************************/

#include <iostream>
using std::cout;

#include <vector>

#include <numeric>
using std::accumulate;

#include <ranges>
// #include <range/v3/all.hpp>
#ifdef RANGES_V3_ALL_HPP
namespace rng = ranges;
#else
namespace rng = std::ranges;
#endif

namespace matlib {

  class vector
    : public std::vector<double> {
  public:
    vector( int n )
      : std::vector<double>(n) {};
    enum norm_type {
      Norm_1, Norm_2, Norm_inf };
    double vecnorm( norm_type typ ) {
      switch (typ) {
      case Norm_1 :
	return accumulate
	  ( begin(),end(), 0.,
	    [] ( auto acc, auto e ) {
	      return acc+std::abs(e); } );
      case Norm_2 : 
	return accumulate
	  ( begin(),end(), 0.,
	    [] ( auto acc, auto e ) {
	      return acc+e*e; } );
      case Norm_inf :
	return accumulate
	  ( begin(),end(), 0.,
	    [] ( auto acc, auto e ) {
	      return std::max( acc,std::abs(e) ); } );
      }
      return 0;
    };
  };

};

int main() {
  
  matlib::vector values(3);
  values[0] = 1; values[1] = 2; values[2] = -3;

  using namespace matlib;
  cout << values.vecnorm
    ( vector::Norm_1 ) << '\n';
  cout << values.vecnorm
    ( vector::Norm_2 ) << '\n';
  cout << values.vecnorm
    ( vector::Norm_inf ) << '\n';

  return 0;
}
