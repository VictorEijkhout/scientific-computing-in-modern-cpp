/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2018-2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** catchquad.cxx : unittesting version of the quadratic exercise
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
#include <sstream>
using std::stringstream;

#include <cmath>

#include <string>
using std::string;

#include <variant>
using std::variant;
using std::get_if;
using std::get;
using std::bad_variant_access;
using std::visit;

#define CATCH_CONFIG_MAIN
#include "catch2/catch_all.hpp"

#include "quadlib.hpp"

TEST_CASE( "discriminant" ) {
  quadratic one{0., 2.5, 0.};
  REQUIRE( discriminant( one ) ==Catch::Approx(6.25) );
  quadratic two{1., 0., 1.5};
  REQUIRE( discriminant( two ) ==Catch::Approx(-6.) );
  quadratic three{.1, .1, .1*.5};
  REQUIRE( discriminant( three ) ==Catch::Approx(-.01) );
}

// in the previous test,
// try also this:
//  REQUIRE( discriminant( make_tuple(.1, .1, .1*.5 ) ) == -.01 );


TEST_CASE( "D = 0" ) {
  double a,b,c,d; bool z;
  string msg;
  SECTION( "simple case" ) {
    msg = "simple case";
    a = 2; b = 4; c = 2;
  }
  SECTION( "interesting case" ) {
    msg = "interesting case";
    a = 2; b = sqrt(40); c = 5;
  }
  SECTION( "b==0" ) {
    msg = "b zero case";
    a = 3; b = 0; c = 0.;
  }
  SECTION( "perturbed case" ) {
    msg = "perturbed case";
    a = 2; b = sqrt(40); c = 5. * (1+1.e-15);
    REQUIRE( c>5. );
  }
  INFO( msg );
  quadratic coefficients{a,b,c};
  d = discriminant( coefficients );
  z = discriminant_zero( coefficients );
  INFO( a << "," << b << "," << c << " d=" << d );
  REQUIRE( z );
  auto r = simple_root(coefficients);
  REQUIRE( evaluate(coefficients,r)==Catch::Approx(0.).margin(1.e-14) );
  //  REQUIRE( evaluate(coefficients,r) ==Catch::Approx(0.) );
}

TEST_CASE( "D != 0" ) {
  double a,b,c,d; bool z;
  SECTION( "double case" ) {
    a = 2; b = sqrt(40); c = 5.1;
  }
  quadratic coefficients{a,b,c};
  d = discriminant( coefficients );
  z = discriminant_zero( coefficients );
  INFO( a << "," << b << "," << c << " d=" << d );
  REQUIRE( not z );
}


TEST_CASE( "double root" ) {
  double a,b,c;
  SECTION( "(x-1)(x-3)" ) {
    a=1; b=-4; c=3;
  }
  quadratic coefficients{a,b,c};
  auto [r1,r2] = double_root(coefficients);
  auto
    e1 = evaluate(coefficients,r1),
    e2 = evaluate(coefficients,r2);
  REQUIRE( evaluate(coefficients,r1)==Catch::Approx(0.).margin(1.e-14) );
  REQUIRE( evaluate(coefficients,r2)==Catch::Approx(0.).margin(1.e-14) );
}

TEST_CASE( "full test" ) {
  double a,b,c; int index;
  SECTION( "no root" ) {
    a=2.0; b=1.5; c=2.5;
    index = 0;
  }
  SECTION( "single root" ) {
    a=1.0; b=4.0; c=4.0;
    index = 1;
  }
  SECTION( "double root" ) {
    a=2.2; b=5.1; c=2.5;
    index = 2;
  }
  quadratic coefficients{.a=a,.b=b,.c=c};
  auto result = compute_roots(coefficients);
  REQUIRE( result.index()==index );
}
