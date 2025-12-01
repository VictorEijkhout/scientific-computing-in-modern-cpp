/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** queuelevel.cxx : unweighted graph through level sets
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
#include <set>
using std::set;

#include <limits>
#include <map>
#include <algorithm>

#include <cassert>

#include <random>

float chance() {
  static  std::default_random_engine static_engine{1};
  std::uniform_real_distribution<float> p(0.f,1.f);
  return p(static_engine);
};

unsigned random_degree( int n ) {
  static  std::default_random_engine static_engine{2};
  std::uniform_int_distribution<> p(n/2,3*n/2);
  return p(static_engine);
};

unsigned random_int( int n ) {
  static  std::default_random_engine static_engine{3};
  std::uniform_int_distribution<> p(0,n-1);
  return p(static_engine);
};

class Dag {
private:
  vector<vector<unsigned>> dag;
public:
  // Make Dag of `n' nodes, no edges for now.
  Dag( unsigned n )
    : dag( vector<vector<unsigned>>(n) ) {};
  const auto& neighbors( unsigned i ) const { return dag.at(i); };
  void make_edges( unsigned avg_degree ) {
    const unsigned n = dag.size();
    assert( avg_degree>=0 and avg_degree<n );
    // each row gets approx `avg_degree' edges
    for ( auto& neighbors: dag ) {
      unsigned degree = random_degree(avg_degree);
      assert(degree>=0 && degree<n);
      for ( unsigned c=0; c<degree; ) {
        unsigned neighbor = random_int(n);
        assert( neighbor>=0 && neighbor<n );
        if ( std::none_of
             ( neighbors.begin(),neighbors.end(),
               [neighbor](unsigned i) { return i==neighbor; } )
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

int main() {

  const unsigned graph_size = 20;
  Dag graph(graph_size); graph.make_edges(4);
  cout << graph.as_string();

  using node_info = std::pair<unsigned,unsigned>;
  std::set< node_info > distances;
  distances.insert( {0,0} );

  for (;;) {
    if (distances.size()==graph_size) break;
    /*
     * Loop over all nodes that are already done
     */
    for ( auto [node,level] : distances ) {
      /*
       * set neighbors of the node to have distance `level + 1'
       */
      const auto& nbors = graph.neighbors(node);
      for ( auto n : nbors ) {
        /*
         * See if `n' has a known distance,
         * if not, add to `distances' with level+1
         */
// answer code removed
          {
            cout << "node " << n << " level " << level+1 << '\n';
            distances.insert( {n,level+1} );
          }
      }
    }
  }

  return 0;
}
