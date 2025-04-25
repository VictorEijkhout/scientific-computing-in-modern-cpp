/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** graphmpv.cxx : graph algorithm through algebra
 ****
 ****************************************************************/

#include <iostream>
using std::cout, std::endl;
#include <iomanip>
using std::setw;
#include <sstream>
using std::stringstream;

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <functional>
using std::function;

using vectorvalue = float;
const vectorvalue infinite = -1;
using matrixvalue = float;
const matrixvalue empty = false;
const matrixvalue filled = true;

//codesnippet adjvecdense
class Vector {
private:
  vector<vectorvalue> values;
public:
  Vector( int n )
    : values( n,infinite ) {};
  //codesnippet end
  //: values( vector<vectorvalue>(n,infinite) ) {};
  // indexing
  vectorvalue& operator[](int i) { return values[i]; };
  int size() const { return values.size(); };
  const vectorvalue& operator[](int i) const { return values[i]; };
  // operations
  void addin( const Vector& other,function< vectorvalue(vectorvalue,vectorvalue) > plus ) {
    const int N = size();
    for ( int e=0; e<N; ++e )
      values[e] = plus(values[e],other[e] );
  };
  // utility
  bool different( const Vector& other ) const {
    bool result = false; const int n = size();
    for ( int i=0; i<n; ++i )
      result = result || ( values[i]!=other[i] );
    return result;
  };
  Vector& unit(int i) { values.at(i) = 0; return *this; };
  string str() const {
    stringstream ss;
    for ( auto v : values )
      if (v==infinite) ss << " .";
      else ss << " " << v;
    return ss.str();
  };
};

//codesnippet adjmatdense
class AdjacencyMatrix {
private:
  vector<vector<matrixvalue>> adjacency;
public:
  AdjacencyMatrix(int n)
    : adjacency( vector<vector<matrixvalue>>
		 ( n,vector<matrixvalue>(n,empty) ) ) {
  };
//codesnippet end
  int size() const { return adjacency.size(); };
  AdjacencyMatrix& diagonal() {
    const int n = size();
    for ( int row=0; row<n; ++row )
      adjacency[row][row] = filled;
    return *this;
  };
  AdjacencyMatrix& circular() {
    const int n = size();
    for ( int row=0; row<n; ++row )
      adjacency[row][ (row+1) % n ] = filled;
    return *this;
  };
  matrixvalue& operator()(int i,int j) {
    return adjacency.at(i).at(j); };
  Vector leftmultiply
      ( const Vector& left,
	function< vectorvalue( vectorvalue,matrixvalue ) > mult,
	function< vectorvalue( vectorvalue,vectorvalue ) > add
	) const {
    const int n = size();
    Vector result(n);
    for ( int row=0; row<n; ++row ) {
      for ( int col=0; col<n; ++col) {
	result[col] = add( result[col], mult( left[row],adjacency[row][col] ) );
      }
    }
    return result;
  };
  string str() const {
    stringstream ss; ss << "\n";
    for ( auto row : adjacency ) {
      for ( auto v : row )
	if (v==empty)
	  ss << " .";
	else ss << setw(3) << v;
      ss << "\n";
    }
    return ss.str();
  };
};
 
int main() {

  cout << "EXAMPLE path\n";
  {
    int N = 5;
    auto circular = AdjacencyMatrix(N).circular();
    circular(0,4) = 5;
    cout << "Shift matrix:" << circular.str();
// answer code removed
    auto distancevector = Vector(N).unit(0);
    cout << "Input : " << distancevector.str() << "\n";
    for ( int step=0; ; ++step ) {
      auto stepvector = circular.leftmultiply
	( distancevector,mult,add );
      auto olddistances = distancevector;
      distancevector.addin( stepvector,add );
      if (not distancevector.different(olddistances))
	break;
      cout << "step " << step << ": " << distancevector.str() << "\n";
    }
  }
  cout << "example path\n";

  return 0;
}
