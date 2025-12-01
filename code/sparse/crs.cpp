/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** crs.cxx : compressed row storage matrix
 ****
 ****************************************************************/

/*
 * Standard libraries
 */
#include <chrono>
#include <cmath>
#include <chrono>
#include <format>
using std::format;
#include <iostream>
using std::cout;
#include <vector>
using std::vector;

/*
 * Other libraries
 */
#include "cxxopts.hpp"

/*
 * This application
 */
#include "crs_mat.hpp"
#include "crs_tests.hpp"

using real = double;

int main( int argc,char **argv ) {

  if ( argc> 1 and ( !strcmp(argv[1],"-u") or !strcmp(argv[1],"--unit") ) ) {
    crs_tests(argc,argv);
    return 0;
  }

  cxxopts::Options options
    ("cxxopts","Sparse matrix demo");
  options.add_options()
    ("h,help","usage information")
    ("u,unit","run unit tests")
    ( "d,dim","dimensionality size",cxxopts::value<int>()->default_value("1") )
    ( "n,nsize","matrix size",cxxopts::value<int>()->default_value("6") )
    ;

  auto result = options.parse(argc, argv);
  if (result.count("help")>0) {
    cout << options.help() << '\n';
    return 0;
  }

  auto nsize = result["nsize"].as<int>();
  auto d = result["dim"].as<int>();
  if (d>1) {
    cout << "No dimensions >1 supported\n";
    return 1;
  }

  using clock = std::chrono::high_resolution_clock;
  auto matrix_size = nsize;

  /*
   * Matrix creation
   */
  auto tstart = clock::now();
  CRSMatrix<real> mat =
    [type=crs_type,matrix_size] () {
      if (type==0)
	return CRSMatrix<real>(matrix_size);
      else
	return CRSMatrix<real>(matrix_size,3);
    }();
  mat.diagonal(0,2.).diagonal(1,-1.).diagonal(-1,-1.);
  auto creation = clock::now()-tstart;

  /*
   * Power method
   */
  Vector<real> x(matrix_size),y(matrix_size);
  x.set(1.);
  tstart = clock::now();
  real nrm;
  for ( int iteration=0; iteration<1000; ++iteration ) {
    mat.times(x,y);
    nrm = y.norm2();
    x.scale( 1./nrm,y );
  }
  auto iteration = clock::now()-tstart;

  auto millisec_duration = std::chrono::duration_cast<std::chrono::milliseconds>(creation);
  cout << "Creation time: " << millisec_duration.count()*1.e-3 << '\n';
  millisec_duration = std::chrono::duration_cast<std::chrono::milliseconds>(iteration);
  cout << "Iteration time: " << millisec_duration.count()*1.e-3 << '\n';
  cout << "final norm: " << nrm << '\n';

  return 0;
};
