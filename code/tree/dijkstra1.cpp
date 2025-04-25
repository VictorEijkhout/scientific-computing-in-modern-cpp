/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** dijkstra1.cxx : shortest path exploration
 ****
 ****************************************************************/

#include <algorithm>
using std::max;

#include <iostream>
using std::cin, std::cout;
#include <iomanip>
using std::setw;
#include <sstream>
using std::stringstream;
#include <string>
using std::string;

#include <random>
#include <vector>
using std::vector;

#include <cassert>

float chance() {
  static  std::default_random_engine static_engine{1};
  std::uniform_real_distribution<float> p(0.f,1.f);
  return p(static_engine);
};

int random_degree( int n ) {
  static  std::default_random_engine static_engine{2};
  std::uniform_int_distribution<> p(n/2,3*n/2);
  return p(static_engine);
};

int random_int( int n ) {
  static  std::default_random_engine static_engine{3};
  std::uniform_int_distribution<> p(0,n-1);
  return p(static_engine);
};

using distance = float;
const distance inf_distance=-1;

#include "levelset.cpp"

class ReachableSet {
private:
  vector<LevelSet> levels;
public:
  ReachableSet( int start )
    : levels( vector<LevelSet>(1, LevelSet(start)) ) {};
  int size() const { return levels.size(); };
  bool has( int node ) const {
    // any of the levels has `node'
    return any_of
      ( levels.begin(),levels.end(),
        [node] ( const LevelSet& level ) {
          return level.has(node); }
        );
  };
  void push_back( LevelSet new_level ) {
    levels.push_back( new_level );
  };
  auto back() { return levels.back(); };
};

//codesnippet dagunweight
class Dag {
private:
  vector<vector<int>> dag;
public:
  // Make Dag of `n' nodes, no edges for now.
  Dag( int n )
    : dag( vector<vector<int>>(n) ) {};
  //codesnippet end
  //codesnippet dagnodenbors
  const auto& neighbors( int i ) const { return dag.at(i); };
  //codesnippet end
  void make_edges( int avg_degree ) {
    const int n = dag.size();
    assert( avg_degree>=0 and avg_degree<n );
    // each row gets approx `avg_degree' edges
    for ( auto& neighbors: dag ) {
      auto degree = random_degree(avg_degree);
      assert(degree>=0 && degree<n);
      for ( int c=0; c<degree; ) {
        int neighbor = random_int(n);
        assert( neighbor>=0 && neighbor<n );
        if ( none_of
             ( neighbors.begin(),neighbors.end(),
               [neighbor](int i) { return i==neighbor; } )
             ) {
          neighbors.push_back(neighbor);
          ++c;
        }
      }
      sort(neighbors.begin(),neighbors.end());
    }
  };
  string as_string() const {
    stringstream ss; int ineighbors=0;
    for (  const auto& neighbors : dag ) {
      ss << ineighbors++ << " => ";
      for ( auto e : neighbors ) ss << setw(3) << e << ", "; ss << '\n';
    }
    return ss.str();
  };
};

bool has( vector<int> level,int n ) {
  return any_of
    (level.begin(),level.end(),
     [n] (int i) { return i==n; });
};

int main() {

  const int graph_size = 20;
  Dag graph(graph_size); graph.make_edges(3);
  //  cout << graph.as_string();
  
// answer code removed
  
  return 0;
}
