/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-9 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** lapack_alloc.cxx : DGEMM using span
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#include <limits>
using std::numeric_limits;

#include <vector>
using std::vector;

#include <chrono>
using namespace std::chrono;

#include "gsl/gsl"
using gsl::span;

#ifdef CBLAS
#include <cblas.h>
#else
// dgemm: TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC
extern "C" {
void dgemm_(char*,char*,int*,int*,int*,
	    double*,double*,int*,
	    double*,int*,
	    double*,double*,int*);
}
#endif

class Matrix {
private:
  int m,n,lda;
  span<double> data;
public:
  Matrix(int m,int lda,int n,double *data)
    : m(m),n(n),lda(lda),
      data( span<double>(data,lda*n) ) {
    if (lda<m) {
      cout << "LDA=" << lda << " lt M=" << m << '\n'; throw(1); }
  };
// answer code removed
  auto get_double_data() {
    double *adata;
    adata = data.data();
    return adata;
  };
// answer code removed
  auto min() {
    auto matdata = get_double_data();
    auto mn = numeric_limits<double>::max();
    for (int j=0; j<n; ++j)
      for (int i=0; i<m; ++i) {
	double v;
#ifdef DEBUG
	try {
	  v = at(i,j);
	} catch (std::out_of_range e) {
	  cout << "min out of range: " << i << "," << j << '\n';
	  throw(1); }
#else
	v = matdata[ i+j*lda ];
#endif
	if (v<mn) mn = v;
      }
    return mn;
  };
  auto max() {
    auto matdata = get_double_data();
    auto mx  = numeric_limits<double>::min();
    for (int j=0; j<n; ++j)
      for (int i=0; i<m; ++i) {
	double v;
#ifdef DEBUG
	try {
	  v = at(i,j);
	} catch (std::out_of_range e) {
	  cout << "max out of range: " << i << "," << j << '\n';
	  throw(1); }
#else
	v = matdata[ i+j*lda ];
#endif
	if (v>mx) mx = v;
      }
    return mx;
  };
  void MatAdd( Matrix& other,Matrix& out ) {
    if (m!=other.m || m!=out.m || n!=other.n || n!=out.n ) {
      cout << "MatAdd: incompatible dimensions" << '\n';
      throw(1); }
    auto adata = get_double_data();
    auto bdata = other.get_double_data();
    auto cdata = out.get_double_data();
    for (int i=0; i<out.m; ++i) {
      for (int j=0; j<out.n; ++j) {
#ifdef DEBUG
	out.at(i,j) = at(i,j) + other.at(i,j);
#else
	cdata[ AT(i,j, out.m,out.n,out.lda) ] =
	  adata[ AT(i,j, m,n,lda) ] + bdata[ AT(i,j, other.m,other.n,other.lda) ];
#endif
      }
    }
  };
  void MatMult( Matrix& other,Matrix& out ) {
    if (n!=other.m || m!=out.m || other.n!=out.n) {
      cout << "MatMult: incompatible dimensions "
	   << "(" << m << "," << n << ") x (" << other.m << "," << other.n << ")"
	   << " -> (" << out.m << "," << out.n << ")"
	   << '\n';
      throw(1); }
    double alpha = 1., beta = 0.;
    auto adata = get_double_data();
    auto bdata = other.get_double_data();
    auto cdata = out.get_double_data();
#ifdef CBLAS
    cblas_dgemm
      ( CblasColMajor, CblasNoTrans, CblasNoTrans,
	m,other.n,n, alpha,adata,lda,
	bdata,other.lda,
	beta,cdata,out.lda);
#else
    for (int i=0; i<out.m; ++i) {
      for (int j=0; j<out.n; ++j) {
    	double s{0};
    	for (int k=0; k<n; ++k) {
#ifdef DEBUG
	  s += at(i,k) * other.at(k,j);
#else
    	  s += adata[ AT(i,k, m,n,lda) ] * bdata[ AT(k,j, other.m,other.n,other.lda) ];
#endif
	}
#ifdef DEBUG
	out.at(i,j) += s;
#else
    	cdata[ AT(i,j, out.m,out.n,out.lda) ] += s;
#endif
      }
    }
    // { char transa='n',transb='n';
    //   dgemm_(  &transa,&transb, &m,&other.n,&n,
    // 	       &alpha,adata,&lda,
    // 	       bdata,&other.lda,
    // 	       &beta,cdata,&out.lda );
    // }
#endif
  };
// answer code removed
  void print() const {
    for (int i=0; i<m; ++i) {
      for (int j=0; j<n; ++j)
	cout << at(i,j) << " ";
      cout << '\n';
    }
  };
};

int main() {

  int M,LDA,N;

  // example values for M,LDA,N
  M = 2; LDA = M+2; N = 3;
  // create a vector to contain the data
  vector<double> one_data(LDA*N,1.);
  // create a matrix using the vector data
  Matrix one(M,LDA,N,one_data.data());

  M = 2; N = 3;
  vector<double> two_data(M*N,2.);
  Matrix two(M,M,N,two_data.data());
  vector<double> three_data(M*N);
  Matrix three(M,M,N,three_data.data());
  one.MatAdd(two,three);
  three.print();

  M=3; N=4; 
  vector<double> tdata(N*M,0.);
  Matrix onet(M,M,N,tdata.data());
  for (int i=0; i<M; ++i)
    for (int j=0; j<N; ++j)
      onet.at(i,j) = j+1;

  cout << "\n2x4:" << '\n';
  vector<double> threes_data(2*4);
  Matrix threes(2,2,4,threes_data.data());
  one.MatMult(onet,threes);
  threes.print();

  cout << "\nleft submatrix:" << '\n';
  auto threeL = threes.Left(2);
  threeL.print();

  cout << "\nright submatrix:" << '\n';
  auto threeR = threes.Right(2);
  threeR.print();

  cout << "\ntop submatrix:" << '\n';
  auto threeT = threes.Top(1);
  threeT.print();

  cout << "\nbot submatrix:" << '\n';
  auto threeB = threes.Bot(1);
  threeB.print();

  cout << "\nMatMult timing:" << '\n';
  {
    int M = 1024, N = 1024;
    //M = 2048; N = 2048;
    vector<double> adata(M*N,1.), bdata(M*N,2.), cdata(M*N,0.);
    Matrix A(M,M,N,adata.data()),B(M,M,N,bdata.data()),C(M,M,N,cdata.data());
    {
      auto start_time = high_resolution_clock::now();
      A.MatMult(B,C);
      auto end_time = high_resolution_clock::now();
      auto duration = duration_cast<milliseconds>(end_time - start_time).count();
      cout << "product took: " << duration << " milliseconds" << '\n';
      cout << "checking:" << '\n';
      auto min = C.min(), max = C.max();
      cout << "C range: " << min << "--" << max << '\n';
    }

    {
      auto start_time = high_resolution_clock::now();
      A.RecursiveMatMult(B,C);
      auto end_time = high_resolution_clock::now();
      auto duration = duration_cast<milliseconds>(end_time - start_time).count();
      cout << "recursive product took: " << duration << " milliseconds" << '\n';
      cout << "checking:" << '\n';
      auto min = C.min(), max = C.max();
      cout << "C range: " << min << "--" << max << '\n';
    }
  }

  return 0;
}
