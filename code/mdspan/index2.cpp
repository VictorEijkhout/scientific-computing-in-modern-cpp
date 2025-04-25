/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2019-2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** transpose.cxx : square matrix transpose through mdspan subspan
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#include <numeric>
using std::reduce;
#include <tuple>
using std::tuple;
#include <vector>
using std::vector;

//#include <ranges>
#include <range/v3/all.hpp>
#ifdef RANGES_V3_ALL_HPP
namespace rng = ranges;
#else
namespace rng = std::ranges;
#endif

// #include <mdspan>

//codesnippet mdspankokkos
#include "mdspan/mdspan.hpp"
namespace md = Kokkos;
namespace KokkosEx = MDSPAN_IMPL_STANDARD_NAMESPACE::MDSPAN_IMPL_PROPOSED_NAMESPACE;
namespace mdx = KokkosEx;
//codesnippet end

int main() {
  constexpr int M=5,N=10;

  //codesnippet mdspan2d
  // matrix in row major
  vector<float> A(M*N);
  md::mdspan
    Amd{ A.data(),M,N };
    // also:  Amd{ A.data(),md::extents{M,N} };
  //codesnippet end
  cout << Amd.extent(0) << " x " << Amd.extent(1) << '\n';

  //codesnippet mdspan2f
  // matrix in column major
  vector<float> B(M*N);
  md::mdspan<float, md::extents<int, M,N>, md::layout_left>
    Bmd{B.data()};
  //codesnippet end

  /*
   * Fill with consecutive integers, row-by-row
   */
  for ( int count=1; auto& e : A )
    e = count++;
  for ( int count=1; auto& e : B )
    e = count++;
  
  /*
   * Row sums
   */
  auto rowsummer = [] ( const auto& mat ) -> void {
    // can't get this to work:
    // auto [M,N] = mat.extents();
    //codesnippet md2drowsum
    int M = mat.extent(0); int N = mat.extent(1);
    vector<float> rowsums(N);
    for ( int row=0; auto& rs : rowsums ) {
      auto the_row =
        rng::iota_view(0,M)
        | rng::views::transform ( [mat,row] (int col) -> float {
            return mat[row,col]; } );
      rs = rng::accumulate( the_row, 0.f );
      row++;
    }
    //codesnippet end
     {
      auto print =
	[init=true] (float rs) mutable {
	  if (init) init=false; else cout << ","; cout << rs ; };
      cout << "Row sums: "; for ( auto rs : rowsums ) print(rs); cout << '\n';
    }
  };
  rowsummer(Amd);
  rowsummer(Bmd);

  /*
   * Column sums
   */
  vector<float> colsums(N);
  for ( int col=0; auto& rs : colsums ) {
    auto the_col =
      rng::views::iota(0,M)
      | rng::views::transform
          ( [Amd,col] (int row) -> float { return Amd[row,col]; } )
      | rng::views::common;
    rs = std::reduce( the_col.begin(),the_col.end(), 0.f );
    col++;
  }
  {
    auto print =
      [init=true] (float rs) mutable {
        if (init) init=false; else cout << ","; cout << rs ; };
    cout << "Col sums: "; for ( auto rs : colsums ) print(rs); cout << '\n';
  }

  return 0;
}
