/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2019-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** transpose.cxx : square matrix transpose through mdspan subspan
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#include <execution>

#include <array>
using std::array;
#include <tuple>
using std::tuple,std::pair;
#include <vector>
using std::vector;

#include <ranges>
//#include <range/v3/all.hpp>
#ifdef RANGES_V3_ALL_HPP
namespace rng = ranges;
#else
namespace rng = std::ranges;
#endif

#include "mdspan/mdspan.hpp"
namespace md = Kokkos;
namespace KokkosEx = MDSPAN_IMPL_STANDARD_NAMESPACE::MDSPAN_IMPL_PROPOSED_NAMESPACE;
namespace mdx = KokkosEx;

int main() {
  constexpr int Nhalf=5, N=2*Nhalf;

  //codesnippet mdspanABalloc
  vector<float> A(N*N),B(N*N);
  for ( int count=1; auto& e : A ) e = count++; //snipexclude
  md::mdspan Amd{ A.data(),N,N };
  md::mdspan Bmd{ B.data(),N,N };
  //codesnippet end

  cout << Amd.extent(0) << " x " << Amd.extent(1) << '\n';
  //codesnippet mdspan2cart
  // (i,j) index pairs into A and B
  auto Aij = rng::views::cartesian_product
    ( rng::views::iota( 0L,static_cast<long int>(Amd.extent(0)) ),
      rng::views::iota( 0L,static_cast<long int>(Amd.extent(1)) )
      );
  //codesnippet end

  //codesnippet mdspan2ij
  std::for_each
    ( std::execution::par_unseq,
      Aij.begin(),Aij.end(),
      [&] ( auto idx ) {
        auto [i,j] = idx;
        Bmd[j,i] = Amd[i,j];
      }
      );
  //codesnippet end

  //codesnippet mdspan2ijspan
  auto TL = md::submdspan( Amd, std::tuple{0,Nhalf},std::tuple{0,Nhalf} );
  auto TR = md::submdspan( Amd, std::tuple{0,Nhalf},std::tuple{Nhalf,N} );
  auto BL = md::submdspan( Amd, std::tuple{Nhalf,N},std::tuple{0,Nhalf} );
  auto BR = md::submdspan( Amd, std::tuple{Nhalf,N},std::tuple{Nhalf,N} );
  //codesnippet end
  //codesnippet mdspan2ijloop
  for ( auto& [tgt,src] :
	  // pairs of A/B tgt/src quadrants
          array< pair<decltype(TL),decltype(TL)>,4 >{
          pair{TL,TL}, pair{BR,BR}, pair{TR,BL}, pair{BL,TR} } ) {
    auto quadrant = rng::views::cartesian_product
      ( rng::views::iota( 0L, static_cast<long int>(tgt.extent(0)) ),
        rng::views::iota( 0L, static_cast<long int>(tgt.extent(1)) )
        );
    std::for_each
      ( quadrant.begin(),quadrant.end(),
        [&] ( auto idx ) {
          auto [i,j] = idx;
          Bmd[j,i] = Amd[i,j];
        }
        );
  }
  //codesnippet end

  return 0;
}
