/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** matrixclass.cxx : wrap an array in a class
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#include <vector>
using std::vector;

//examplesnippet matrixclassdef
class matrix {
private:
  vector<double> matrix_data;
  int m,n;
public:
  matrix(int m,int n)
    : m(m),n(n),matrix_data(m*n) {};
  //examplesnippet end
  //examplesnippetcont matrixclassmeth
  void setij(int i,int j,double v) {
    matrix_data.at( i*n +j ) = v;
  };
  double getij(int i,int j) {
    return matrix_data.at( i*n +j );
  };
  //examplesnippet end
  double &element(int i,int j) {
    return matrix_data.at( i*n +j );
  };
// answer code removed
};
  
int main() {

  matrix A(20,30);

  A.setij(0,1,5.14);
  cout << "Just set (0,1) to " << A.getij(0,1) << '\n';

  //examplesnippet matrixelement
  A.element(2,3) = 7.24;
  cout << "Just set (2,3) to " << A.getij(2,3) << '\n';
  //examplesnippet end

  return 0;
}
