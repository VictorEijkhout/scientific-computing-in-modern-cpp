/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2023-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** pacific.cxx : garbage patch simulation
 ****
 ****************************************************************/

#include <iostream>
#include <iomanip> 
#include <fstream>
using std::cout,std::cin,std::endl,std::ostream,std::ofstream,std::setw;

#include <algorithm>
#include <array>
#include <chrono>
using std::chrono::seconds;
#include <cmath>
#include <numeric>
#include <optional>
using std::optional;
#include <random>
using std::default_random_engine,std::random_device,std::mt19937,
  std::uniform_real_distribution,std::uniform_int_distribution;
// #include <ranges>
#include <range/v3/all.hpp>

#include <string>
using std::string;
#include <thread>
#include <tuple>
using std::pair;
#include <vector>
using std::vector;

#include <cstdio>
#include <unistd.h>

#include "cxxopts.hpp"

// using namespace std;

// answer code removed
// answer code removed

class ocean {
private:
  // careful: declarations in this order because of constructor!
  int iSize,jSize;
  vector<occupy> ocean_;
  float junk_rate{0.f},turtle_rate{0.f};
public:
  /*
   * Constructor
   */
  ocean(int size,
	 float trash_f,float junk_rate,
	 float turtle_f,float turtle_rate,
	 float ship_f )
    : iSize(size),jSize(size)
    , ocean_( vector<occupy>(iSize*jSize,occupy::empty) )
    , junk_rate( junk_rate/(iSize*jSize) )
    , turtle_rate( turtle_rate ) {
    for ( auto [i,j] : permuted_indices( ship_f  * (iSize*jSize) ) )
      cell(i,j) = occupy::ship;
    for ( auto [i,j] : permuted_indices( trash_f * (iSize*jSize) )  )
      cell(i,j) = occupy::trash;
    for ( auto [i,j] : permuted_indices( turtle_f* (iSize*jSize) ) )
      cell(i,j) = occupy::turtle;
  };
  int index( int i,int j ) const { return i*jSize+j; };
  occupy cell( int i,int j ) const { return ocean_.at(index(i,j)); };
  occupy& cell( int i,int j )      { return ocean_.at(index(i,j)); };

  int count( occupy typ ) const {
    int cnt{0};
    ranges::for_each( ocean_, [&cnt,typ] (occupy t) { if (t==typ) ++cnt; } );
    return cnt;
  };
  
// answer code removed

// answer code removed
public:
// answer code removed

  auto get_nth( int n,occupy label, int ic, int jc) const {
    int count = 0;
    for ( auto [i,j] : neighbors(ic,jc) ) {
      if (cell(i,j) == label) {
	if (count == n)
	  return pair<int,int>(i,j);
	++count;
      }
    }
    return pair<int,int>(-1,-1);
  };

  int count_around( int ic,int jc,occupy typ ) const {
    int count=0;
    for ( auto [i,j] : neighbors(ic,jc) ) {
      if (cell(i,j) == typ)
	++count;
    }
    return count;
  };

  optional< pair<int,int> > random_neighbor(int i,int j,occupy typ,double p=0.) const {
    if ( int count = count_around(i,j,typ); count==0 )
      return {};
    else {
      if ( p==0. or ( random_fraction()<p ) ) {
	int n = random_index(count);
	return get_nth(n,typ,i,j);
      } else return {};
    }
  };
  
  void update() {
    ocean prev(*this);
    
    for ( auto [i,j] : permuted_indices() ) {
      /*
       * Turtle
       * 1. if next to trash, it dies
       * 2. otherwise move to empty spot
       */
      if ( prev.cell(i,j) == occupy::turtle ) {
	auto ixiy = random_neighbor(i,j,occupy::trash);
	// Trash : the turtle diese
	if (ixiy.has_value()) { // there is trash!
	  cell(i,j) = occupy::empty;
	} else if ( turtle_rate>0 and random_fraction()<turtle_rate ) {
	  auto ixiy = random_neighbor(i,j,occupy::empty);
	  if (ixiy.has_value()) {
	    auto [ix,iy] = ixiy.value();
	    cell(ix,iy) = occupy::turtle;
	  }
	} else {
	  // move to empty neighbor
	  auto ixiy = random_neighbor(i,j,occupy::empty);
	  if (ixiy.has_value()) {
	    auto [ix,iy] = ixiy.value();
	    cell(ix,iy) = prev.cell(i,j);
	    cell(i,j) = occupy::empty;
	  }
	}
      } else if ( prev.cell(i,j) == occupy::ship) {
	/*
	 * Ship
	 * 1. if next to trash, clear it 
	 * 2. otherwise move to empty spot
	 */
	// let this ship clear a random piece of trash, or just move
	auto ixiy = random_neighbor(i,j,occupy::trash);
	if (ixiy.has_value()) { // there is trash!
	  auto [ix,iy] = ixiy.value();
	  cell(ix,iy) = prev.cell(i,j);
	  cell(i,j) = occupy::empty;
	} else {
	  auto ixiy = random_neighbor(i,j,occupy::empty);
	  if (ixiy.has_value()) { // we can move
	    auto [ix,iy] = ixiy.value();
	    cell(ix,iy) = prev.cell(i,j);
	    cell(i,j) = occupy::empty;
	  }
	} // case of breeding turtle?
      } else if ( prev.cell(i,j)==occupy::empty ) {
	/*
	 * Empty: maybe new trash
	 */
	if ( junk_rate>0 and random_fraction()<junk_rate )
	  cell(i,j) = occupy::trash;
      }
    } // end of loop over indices
  };

public:
  float random_fraction() const {
    //    static mt19937 random_generator;
    uniform_real_distribution<float> fraction_dist(0.f,1.f);
    return fraction_dist(random_generator);
  };
  int random_index(int n) const {
    // static mt19937 random_generator;
    uniform_int_distribution<int> int_dist(0,n-1);
    return int_dist(random_generator);
  };

public:
  auto print_info(int ts,bool print=false) const {
    int
      t = count(occupy::turtle),
      j = count(occupy::trash),
      s = count(occupy::ship);
    if (print) {
      if (ts>=0) cout << "T=" << ts << ": ";
      cout
	<< "Turtles: " << t << " "
	<< "Trash: " << j << " "
	<< "Ship: " << s << " "
	<< '\n';
    }
    return pair<int,int>(t,j);
  }

  void print_ocean( string fileName) const {
    ofstream myFile;
    myFile.open(fileName);
    for (int i = 0; i < iSize; ++i){
      for (int j = 0; j < jSize; ++j){
	myFile << cell(i,j) << " ";
      }
      myFile << endl;
    }
    myFile.close();
  }

  void trace_view() const {
    // ESC [ i ; j H
    printf( "%c[0;0H",(char)27);
    const int hs=3;
    // top numbering
    cout << "  "; for ( int j=0; j<jSize; ++j ) cout << setw(hs) << j%10; cout << '\n';
    // ocean
// answer code removed
    cout << "Turtles: " << count(occupy::turtle) << '\n'
	 << "Trash  : " << count(occupy::trash) << '\n'
	 << "Ships  : " << count(occupy::ship) << '\n';
    std::this_thread::sleep_for( seconds{2}/10. );
  };
};

int main (int argc,char **argv){

  cxxopts::Options options
    ("cxxopts", "Commandline options demo");
  options.add_options()
    ("h,help","usage information")

    ("n,nsize","size of square", cxxopts::value<int>()->default_value("100") )
    ("m,time", "time steps",     cxxopts::value<int>()->default_value("100") )

    ("t,turtle","fraction of turtles",cxxopts::value<float>()->default_value(".01") )
    ("j,junk","amount of junk",       cxxopts::value<float>()->default_value(".01") )
    ("s,ship","density of ships",     cxxopts::value<float>()->default_value(".01") )

    ("J,junk_rate","new junk per step",     cxxopts::value<float>()->default_value(".0") )
    ("T,turtle_rate","new turtles per step",cxxopts::value<float>()->default_value(".0") )
    ("v,view","trace iterations")
    ("V,View","pictorial view")
    ;

  auto result = options.parse(argc, argv);
  if (result.count("help")>0) {
    cout << options.help() << '\n';
    return 0;
  }
  bool trace_iteration = ( result.count("view")>0 );
  bool trace_ocean = ( result.count("View")>0 );
  auto nsize = result["nsize"].as<int>();
  float
    turtle_f  = result["turtle"].as<float>(),
    trash_f   = result["junk"]  .as<float>(),
    ship_f    = result["ship"]  .as<float>();
  float
    junk_rate = result["junk_rate"].as<float>(),
    turtle_rate = result["turtle_rate"].as<float>();
  cout << turtle_f << " " << trash_f << " " << ship_f << '\n';

  ocean pacific( nsize,
		  trash_f,junk_rate,
		  turtle_f,turtle_rate,
		  ship_f);

  auto steps = result["time"].as<int>();

  vector<int> turtle_hist,trash_hist;
  for (int istep=0; istep<steps; ++istep) {
    
    //    pacific.update_values(); 
    pacific.update();

    auto [t,j] = pacific.print_info(istep,trace_iteration);
    turtle_hist.push_back(t); trash_hist.push_back(j);
    if (trace_ocean)
      pacific.trace_view();
  }

  {
    auto print_t = [init=true] ( int t ) mutable {
      if (init) {
	cout << "Turtle: " << t; init=false;
      } else cout << " " << t; };
      for ( auto t : turtle_hist )
	print_t(t);
    cout << '\n';
  }
  {
    auto print_t = [init=true] ( int t ) mutable {
      if (init) {
	cout << "Trash: " << t; init=false;
      } else cout << " " << t; };
      for ( auto t : trash_hist )
	print_t(t);
    cout << '\n';
  }
  return 0;
}

