/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** queuedijkstra.cxx : weighted graph sssp with queues
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
        if ( none_of
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

  const unsigned inf = std::numeric_limits<unsigned>::max();
  using node_info = std::pair<unsigned,unsigned>;
  std::set< node_info > distances,to_be_done;
  
  to_be_done.insert( {0,0} );
  for (unsigned n=1; n<graph_size; ++n)
    to_be_done.insert( {n,inf} );

  for (;;) {
    if (to_be_done.size()==0) break;
    /*
     * Find the node with least distance
     */
    auto closest_node = min_element
      ( to_be_done.begin(),to_be_done.end(),
        [] ( const node_info& x,const node_info& y ) { return x.second < y.second ; }
        );
    auto [nclose,dclose] = *closest_node;
    cout << "min: " << nclose << " @ " << dclose << '\n';
    /*
     * Move that node to done,
     */
    to_be_done.erase(closest_node);
    distances.insert( *closest_node );
    /*
     * set neighbors of nclose to have that distance + 1
     */
    const auto& nbors = graph.neighbors(nclose);
    for ( auto n : nbors ) {
      // find `n' in distances
      const auto dfind = std::find_if
        ( distances.begin(),distances.end(), [n] (auto d) { return d.first==n; } );
      if (dfind==distances.end() )
        {
          /*
           * if `n' does not have known distance,
           * find where it occurs in `to_be_done' and update
           */
// answer code removed
          to_be_done.erase( cfind );
          to_be_done.insert( {n,dclose+1} );
        }
    }
  }

  return 0;
}
