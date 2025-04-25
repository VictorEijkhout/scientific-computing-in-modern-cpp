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

#include <functional>
#include <vector>

class Vector : public std::vector<float> {
public:
  Vector(int s ) : vector<float>(s) {};
};

void pointwisemult( const Vector& d,const Vector& in,Vector& out ) {};

//codesnippet matfuncinherit
class Matrix {
public:
  Matrix();
  std::function< void(const Vector&,Vector&) > multiply;
};

class DiagonalMatrix : public Matrix {
private:
  Vector diagonal;
public:
  DiagonalMatrix( const Vector& d )
    : Matrix::Matrix(), diagonal(d) {
    multiply = [*this] (const Vector& in,Vector& out) {
      pointwisemult( diagonal,in,out ); };
  };
};

int main() {
  Vector diag(100);
  Matrix m = DiagonalMatrix(diag);
  Vector invector(100),outvector(100);
  m.multiply(invector,outvector);
  return 0;
};
//codesnippet end

Matrix::Matrix() {};
