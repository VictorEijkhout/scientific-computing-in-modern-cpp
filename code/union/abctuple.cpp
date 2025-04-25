/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2018-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** actuple.cpp : abc formula
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <cmath>
#include <string>
using std::string;

#include <optional>
using std::optional;

#include <tuple>
using std::pair, std::make_pair, std::tuple, std::make_tuple;
#include <variant>
using std::variant, std::monostate;

//codesnippet quadtypedef
using quadratic = tuple<double,double,double>;
//codesnippet end

//codesnippet quaddiscriminant
double discriminant
    ( quadratic q ) {
  auto [a,b,c] = q;
  return b*b-4*a*c;
}
//codesnippet end

// assuming there are two roots, return as pair
pair<double,double> abc_roots( quadratic q );

// say either "one" or "two", or say nothing
//codesnippet quadoptstring
optional<string> how_many_roots( quadratic q );
//codesnippet end

// answer code removed

int main() {

  /*
   * Initialization syntax is not unique
   */
  { 
    // spell it out
    auto sunk = tuple<double,double,double>{1.,0.,-2};
  }
  {
    // brace syntax
    auto sunk = quadratic{1.,0.,-2};
  }

  /*
   * Here is the actual program
   */
  // parenthesis syntax
  //codesnippetcont quadtypedef
  // polynomial: x^2 - 2
  auto sunk = quadratic(1.,0.,-2);
  //codesnippet end
  auto [a,b,c] = sunk;
  cout << "coefficients: " << a << "," << b << ',' << c << '\n';

  //codesnippet quaddiscruse
  auto d = discriminant( sunk );
  cout << "discriminant: "
       << d << '\n';
  //codesnippet end

  //codesnippet abcoptnumuse
  auto num_solutions = how_many_roots(sunk);
  if ( not num_solutions.has_value() )
    cout << "none\n";
  else
    cout << num_solutions.value() << '\n';
  //codesnippet end

  //codesnippet abcroottest
  auto roots = abc_roots( sunk );
  auto [xplus,xminus] = roots;
  cout << xplus << "," << xminus << '\n';
  //codesnippet end

  //codesnippet abcvariantcases
  auto root_cases = abc_cases( sunk );
  switch (root_cases.index()) {
  case 0 : cout << "No roots\n"; break;
  case 1 : cout << "Single root: " << get<1>(root_cases); break;
  case 2 : {
    auto xs = get<2>(root_cases);
    auto [xp,xm] = xs;
    cout << "Roots: " << xp << "," << xm << '\n';
  } ; break;
  }
  //codesnippet end

  return 0;
}

// answer code removed

// answer code removed
