/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** crs_mat.cpp : implementation of CRS storage
 ****     common routines to all schemes
 ****     specific constructor/insertion routines are in crs_mat0/1.cpp
 ****
 ****************************************************************/

#include "crs_mat.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>

#include <format>
#include <iostream>
#include <vector>

/*
 * Vector class
 */
template< typename scalar >
Vector<scalar>::Vector( idxint n ) : elements(n) {};
template< typename scalar >
Vector<scalar>::Vector( idxint n,scalar v ) : elements(n,v) {};


template< typename scalar >
void Vector<scalar>::scale( scalar value ) {
  for ( idxint i=0; i<elements.size(); ++i )
    elements[i] *= value;
};

template< typename scalar >
void Vector<scalar>::scale( scalar factor,const Vector<scalar>& in ) {
  for ( idxint i=0; i<elements.size(); ++i )
    elements[i] = in.elements[i] * factor;
};

template< typename scalar >
void Vector<scalar>::set( scalar value ) {
  for ( idxint i=0; i<elements.size(); ++i )
    elements[i] = value;
};

//codesnippet crsvectornormdecl
template< typename scalar >
scalar Vector<scalar>::norm2() const {
  scalar s=static_cast<scalar>(0);
  for ( auto e : elements )
    s += e*e;
  return std::sqrt(s);
};
//codesnippet end

/*
 * CRS Matrix class
 */

/*
 * Number of nonzeros in a row
 * or in total if given an invalid row number
 */
template< typename scalar >
idxint CRSMatrix<scalar>::nnonzeros( int64_t row) const {
  if ( row>=0 and row<rowsize() )
    return rowlen.at(row);
  else {
    idxint n{0};
    for ( idxint i=0; i<m_; ++i )
      n += rowlen.at(i);
    return n;
  }
};

/*
 * Summ of elements in a given row
 */
template< typename scalar >
scalar CRSMatrix<scalar>::rowsum( int64_t row) const {
  scalar s{0};
  for ( idxint i=0; i<rowlen.at(row); ++i )
    s += elements.at( rowptr.at(i)+i );
  return s;
};

template< typename scalar >
CRSMatrix<scalar>& CRSMatrix<scalar>::diagonal( idxint idiagonal,scalar value ) {
  for ( idxint row=std::max<idxint>(0,-idiagonal);
	row<std::min<idxint>(m_,m_-idiagonal);
	++row) {
    idxint col = row+idiagonal;
    set(row,col,value);
  }
  return *this;
};

template< typename scalar >
void CRSMatrix<scalar>::scale( scalar factor ) {
  for ( idxint row=0; row<rowsize(); ++row ) {
    for ( idxint icol=rowptr[row]; icol<rowptr[row]+rowlen[row]; ++icol ) {
      elements[icol] *= factor;
    }
  }
};

//codesnippet crsmatmult
template< typename scalar >
void CRSMatrix<scalar>::times( const Vector<scalar>& in,Vector<scalar>& out ) const {
  for ( idxint row=0; row<out.size(); ++row ) {
    assert(out.size()==m_); //snipexclude
    scalar s{0};
    for ( idxint icol=rowptr[row]; icol<rowptr[row]+rowlen[row]; ++icol ) {
      assert(icol>=0); assert(icol<elements.size()); //snipexclude
      auto col = colidx[icol];
      assert(col>=0); assert(col<m_); //snipexclude
      auto aij = elements[icol];
      auto x   = in[col];
      s += aij * x;
    }
    out[row] = s;
  }
};
//codesnippet end

template class Vector<float>;
template class Vector<double>;

template class CRSMatrix<float>;
template class CRSMatrix<double>;
