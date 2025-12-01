/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** stencil.cxx : block toeplitz matrix for stencils
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
#include <print>
using std::println;

#include <chrono>
using namespace std::chrono;
using myclock = system_clock;

#include <cassert>
#include <cmath>
using std::min,std::max;
#include <format>
using std::format;
//#include <ranges>
//namespace rng = std::ranges;
#include <tuple>
using std::pair,std::tuple,std::make_tuple;
#include <vector>


using FloatType = double;
using idxint = std::int64_t;

template< typename F >
class Vector : private std::vector<F> {
public:
  using std::vector<F>::begin;
  using std::vector<F>::end;
  using std::vector<F>::vector;
private:
  idxint m,n;
public:
  Vector( idxint m,idxint n )
    : m(m),n(n),std::vector<F>::vector<F>(m*n) {};
  F operator[]( idxint i,idxint j ) const;
  F& operator[]( idxint i,idxint j );
  auto dimensions() const {
    return make_tuple(m,n); };
  // math functions
  F norm() const {
    F s=0;
    for ( auto e : *this )
      s += e*e;
    return std::sqrt(s);
  };
  void scale( F factor ) {
    for ( auto& e : *this )
      e *= factor;
  };
  void copy_from( const Vector<F>& in ) {
    std::copy(in.begin(), in.end(), this->begin());
  };
};

template< typename F >
using Leg = tuple<int,int,F>;

template< typename F >
class StencilMatrix {
private:
  std::vector<Leg<F>> legs;
public:
  StencilMatrix
      ( const std::vector<Leg<F>>& legs )
    : legs(legs) {};
  void times( const Vector<F>& rhs,Vector<F>& lhs ) const {
    // vector dimensions; enforce agreement
    auto [m,n] = rhs.dimensions();
    auto [mm,nn] = lhs.dimensions();
    assert( m==mm and n==nn );

    std::fill(lhs.begin(), lhs.end(), F(0)); //snipexclude

    for ( auto [ishift,jshift,v] : legs )
      for ( idxint i=std::max(0,0-ishift); 
                   i<std::min(m,m-ishift); ++i )
        for ( idxint j=std::max(0,0-jshift); 
                     j<std::min(n,n-jshift); ++j )
          lhs[i,j] += v * rhs[i+ishift,j+jshift];
  };
      // try {
      // } catch (...) { println("Error in leg [{},{}]",ishift,jshift); throw; }
// answer code removed
// answer code removed
        auto nrm = v.norm();
        v.scale( 1./nrm );
        u.copy_from( v );
        history.push_back(nrm);
        max_norm = nrm;
      }
      auto duration = myclock::now()-tstart;
      auto millisec_duration = duration_cast<milliseconds>(duration);
      auto tsec = millisec_duration.count()*1.e-3;
      if (xp==1)
        println("Time for regular product: {}, final value={}",
                tsec,history.back());
      else if (xp==2)
        println("Time for flipped product: {}, final value={}",
                tsec,history.back());
    }
  }

  return 0;
};
