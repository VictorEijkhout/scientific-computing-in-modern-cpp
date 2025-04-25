/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2020-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** compare.cpp :  compare random walks with std::array and std::vector
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <chrono>
using std::chrono::high_resolution_clock, std::chrono::duration_cast, std::chrono::milliseconds;
#include <vector>
using std::vector;
#include <array>
using std::array;
#include <random>
using std::random_device, std::mt19937, std::normal_distribution;

template< typename VECTOR >
float norm( const VECTOR& v ) {
  float sum = 0;
  for ( auto x : v )
    sum += x*x;
  return std::sqrt(sum);
}

float random_float() {
  return 1.f;
  static random_device rd;
  static mt19937 gen(rd());
  static normal_distribution<float> dis(0.0, 1.0);
  return dis(gen);
}

//codesnippet walkvec
template< typename VECTOR >
void random_vector( VECTOR& v );
//codesnippet end

//codesnippet walkwalk1
vector<float> random_walk_1( int steps ) {
  vector<float> result(3);
  for (int s=0; s<steps; ++s) {
    vector<float> update(3);
    random_vector<vector<float>>( update );
    for ( auto i : {0,1,2} )
      result[i] += update[i];
  }
  return result;
}
//codesnippet end

//codesnippet walkwalk2
array<float,3> random_walk_2( int steps ) {
  array<float,3> result = {0,0,0};
  for (int s=0; s<steps; ++s) {
    array<float,3> update{};
    random_vector<array<float,3>>
      ( update );
    for ( auto i : {0,1,2} )
      result[i] += update[i];
  }
  return result;
}
//codesnippet end

//codesnippet walkwalk3
void random_walk_3( vector<float>* result, vector<float>* update,int steps ) {
  for (int s=0; s<steps; ++s) {
    random_vector<vector<float>>( *update );
    for ( auto i : {0,1,2} )
      (*result)[i] += (*update)[i];
  }
}
//codesnippet end

int main() {

  for ( auto test : {1,2,3} ) {
    auto start_time = high_resolution_clock::now();
    auto steps = 500'000'000;
    float distance = 0;
    //codesnippet walkwalkmain
    if (test==1) {
      vector<float> travel;
      travel = random_walk_1(steps);
      distance = norm(travel);
    } else if (test==2) {
      array<float,3> travel; 
      travel = random_walk_2(steps);
      distance = norm(travel);
    } else if (test==3) {
      vector<float> travel(3);
      vector<float> step(3);
      random_walk_3(&travel, &step, steps);
      distance = norm(travel);
    }
    //codesnippet end
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time).count();
    cout << "Test " << test << ": distance: " << distance << '\n';
    cout << "run took: " << duration << " milliseconds" << '\n';
    
  }

  return 0;
}

template< typename VECTOR >
void random_vector( VECTOR& v ) {
  float sum = 0;
  for ( auto& x : v ) {
    x = random_float();
    sum += x*x;
  }
  auto nrm = std::sqrt(sum);
  for ( auto& x : v )
    x /= nrm;
}

