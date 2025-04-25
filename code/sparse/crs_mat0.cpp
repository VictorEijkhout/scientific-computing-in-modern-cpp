/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2024-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** crs_mat0.cpp : implementation of CRS storage
 ****     using dynamic extension
 ****
 ****************************************************************/

#include "crs_mat.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>

#include <format>
using std::format;
#include <iostream>
using std::cout;
#include <vector>

int crs_type = 0;

/*
 * CRS Matrix class
 */
template< typename F >
CRSMatrix<F>::CRSMatrix( idxint m,idxint nonzeros_per_row )
  : m_(m) // row size
  , rowptr  (m_+1) // allocate one more pointer than the row size
  , rowlen  (m_) // length of each row
  , colidx  ( std::max<idxint>( m_*nonzeros_per_row,1 ) )
  , elements(m_*nonzeros_per_row) // actual value per element
{
  if (m<=0) // what is allocated in this case?
    throw( std::format("Matrix sizes needs to be positive, not {}",m) );
  if (nonzeros_per_row>0)
    throw( std::format("CRS type 0 has to start empty") );

  // construct row pointers and column indices iteratively
  //codesnippet crsconstruct0
  colidx.at(0) = 0; rowptr.at(0) = 0;
  for ( idxint row=0; row<m_; ++row ) {
    rowlen.at(row) = 0;
    rowptr.at(row+1) = rowptr.at(row) + rowlen.at(row);
    if (row<m_-1)
      colidx.at( rowptr.at(row+1) ) =
        colidx.at( rowptr.at(row) ) + nonzeros_per_row;
  }
  //codesnippet end
};

/*!
 * Set a matrix element
 * For now we don't allow overwriting:
 * each `set' command tries to create a new nonzero
 */
//codesnippet crsset0decl
template< typename F >
void CRSMatrix<F>::set( idxint i,idxint j,F v ) {
//codesnippet end
  // catch obvious errors
  if ( i<0 or j<0 or i>=m_ or j>=m_ )
    throw(std::format("Invalid insert index i={} j={}",i,j));

  if (rowlen.at(i)==m_) 
    throw( std::format("Can not insert: row {} is already full",i) );
  //codesnippet crsset0
  auto insertloc = rowptr.at(i)+rowlen.at(i); //rowptr.at(i+1);
  colidx  .insert( colidx  .begin()+insertloc, j );
  elements.insert( elements.begin()+insertloc, v );
  rowlen.at(i) += 1;
  for ( int row=i+1; row<=m_; ++row )
    rowptr.at(row)++;
  //codesnippet end
};

template class Vector<float>;
template class Vector<double>;

template class CRSMatrix<float>;
template class CRSMatrix<double>;

