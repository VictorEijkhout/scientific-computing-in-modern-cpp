#include <iostream>
using std::cout,std::cin;

#include <Eigen/Dense>
using Eigen::Matrix, Eigen::Dynamic;
 
int main()
{
  int size =
    [] () { int size; cin >> size; return size; }();

  // typedef: MatrixXf
  Matrix<float,Dynamic,Dynamic> A(1,1);
  A.resize(size,2);
  for ( int row=0; row<A.rows(); ++row)
    for (int col=0; col<A.cols(); ++col )
      A(row,col) = 1./(1.+row+col);
  Eigen::Vector<float,2> x;
  Eigen::Vector<float,Eigen::Dynamic> b(size);

  // check conforming dimensions
  b = A*x;

  // compute x through Moore-Penrose inverse
  auto gen_inverse = ( A.transpose() * A ).inverse() * A.transpose();
  x = gen_inverse *b;

  cout << "slope=" << x(0) << ", intercept=" << x(1) << '\n';
  
  return 0;
}
