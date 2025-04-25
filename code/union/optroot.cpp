/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2019-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** optional.cxx : optional results
 ****
 ****************************************************************/


#include <iostream>
using std::cin;
using std::cout;

#include <cmath>

//codesnippet rootandvalid
#include <tuple>
using std::tuple, std::pair;
//codesnippet end

// answer code removed

#include <optional>
using std::optional;

//codesnippet rootorerror
bool RootOrError(float &x) {
  if (x<0)
    return false;
  else
    x = std::sqrt(x);
  return true;
};
//codesnippet end

//codesnippet rootandvalid
pair<bool,float> RootAndValid(float x) {
  if (x<0)
    return {false,x};
  else
    return {true,std::sqrt(x)};
};
//codesnippet end

// answer code removed

// answer code removed

int main() {

  float x;
  x = 2;
  //codesnippet rootorerroruse
  for ( auto x : {2.f,-2.f} ) 
    if (RootOrError(x))
      cout << "Root is "
           << x << '\n';
    else
      cout
        << "could not take root of "
        << x << '\n';
  //codesnippet end

  //codesnippet rootandvalid
  for ( auto x : {2.f,-2.f} ) 
    if ( auto [ok,root] = RootAndValid(x) ; ok )
      cout << "Root is "
           << root << '\n';
    else
      cout
        << "could not take root of "
        << x << '\n';
  //codesnippet end
  
  //codesnippet rootvariantuse
  for ( auto x : {2.f,-2.f} ) {
    auto okroot = RootVariant(x);
    auto root = get_if<float>(&okroot); 
    if ( root )
      cout << "Root is "
           << *root << '\n';
    auto nope = get_if<bool>(&okroot);
    if (nope)
      cout
        << "could not take root of "
        << x << '\n';
  }
  //codesnippet end
  
  //codesnippet mayberootptr
  for ( auto x : {2.f,-2.f} ) 
    if ( auto root = MaybeRoot(x);
         root.has_value() )
      cout << "Root is "
           << root.value()
           << '\n';
    else
      cout
        << "could not take root of "
        << x << '\n';
  //codesnippet end

  //codesnippet mayberootptrstar
  for ( auto x : {2.f,-2.f} ) 
    if ( auto root = MaybeRoot(x) ; root )
      cout << "Root is "
           << *root << '\n';
    else
      cout
        << "could not take root of "
        << x << '\n';
  //codesnippet end

  cout << "Monadic\n";
  //codesnippet maybemonadic
  optional<float> MaybeRoot(float x);
  for ( auto x : {2.f,-2.f} ) 
    MaybeRoot(x)
      .transform( [] ( float x ) { return x*x; } )
      .and_then( [] (float x ) -> optional<float> {
          cout << "check root is: "
               << x << '\n'; return x; } );
  //codesnippet end
  cout << "monadic\n";

  return 0;
}

