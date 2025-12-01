/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** testzero.cxx : unittests for root finding
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
#include <iomanip>
using std::setw;

#include <vector>
using std::vector;

#include "findzerolib.hpp"

#define CATCH_CONFIG_MAIN
#include "catch2/catch_all.hpp"

TEST_CASE( "coefficients represent polynomial" "[1]") {
  vector<double> coefficients = { 1.5, 0., -3 };
  REQUIRE( coefficients.size()>0 );
  REQUIRE( coefficients.front()!=0. );
}

// answer code removed

// answer code removed

// answer code removed

TEST_CASE( "outer bounds","[5]" ) {
  double left{10},right{11};
  right = left+1;
  polynomial second{2,0,1}; // 2x^2 + 1
  REQUIRE_THROWS( find_initial_bounds(second,left,right) );
  polynomial third{3,2,0,1}; // 3x^3 + 2x^2 + 1
  REQUIRE_NOTHROW( find_initial_bounds(third,left,right) );
  REQUIRE( left<right );
  double
    leftval = evaluate_at(third,left),
    rightval = evaluate_at(third,right);
  REQUIRE( leftval*rightval<=0 );
}

TEST_CASE( "outer bounds loop","[5]" ) {
  for ( auto oddpoly : vector<polynomial>{
      {1., 0., 0., 0.}, {.01, 0., 0., 0., 0., 100000.}
    } ) {
    double left{10},right{11};
    REQUIRE_NOTHROW( find_initial_bounds(oddpoly,left,right) );
    REQUIRE( left<right );
    double
      leftval = evaluate_at(oddpoly,left),
      rightval = evaluate_at(oddpoly,right);
    REQUIRE( leftval*rightval<=0 );
  }
}

TEST_CASE( "move bounds closer","[6]" ) {
  double left{10},right{11};
  polynomial third{3,2,0,1}; // 3x^3 + 2x^2 + 1
  REQUIRE_NOTHROW( find_initial_bounds(third,left,right) );
  double
    leftval = evaluate_at(third,left),
    rightval = evaluate_at(third,right);
  REQUIRE( leftval*rightval<=0 );
  REQUIRE_THROWS( move_bounds_closer(third,right,left) );
  REQUIRE_THROWS( move_bounds_closer(third,left,left) );
  double old_left = left, old_right = right;
  REQUIRE_NOTHROW( move_bounds_closer(third,left,right) );
  leftval = evaluate_at(third,left);
  rightval = evaluate_at(third,right);
  REQUIRE( leftval*rightval<=0 );
  REQUIRE( ( ( left==old_left and right<old_right ) or
	     ( right==old_right and left>old_left ) ) );
}

TEST_CASE( "test zero finder", "[7]" ) {
  vector<polynomial> polynomials{
    {1., 0., 0., 0.01}, // x^3, 3x^2
    {.01, 0., 0., 0., 0., 100000.} // 1/100 x^5 + 10,000 , 1/20 x^4
  };
  for ( int ipoly=0; ipoly<polynomials.size(); ++ipoly ) {
    auto oddpoly = polynomials.at(ipoly);
    INFO( "polynomial #" << ipoly );
    double zero, value, prec=1.e-5;
    REQUIRE_NOTHROW( zero = find_zero(oddpoly,prec) );
    INFO( "found zero=" << zero );
    REQUIRE_NOTHROW( value = evaluate_at(oddpoly,zero) );
    REQUIRE( std::abs(value)<prec );
  }
}
