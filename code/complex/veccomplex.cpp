/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** veccomplex.cxx : vector of complexes
 ****
 ****************************************************************/

#include <iostream>
using std::cin, std::cout;
#include <print>
using std::println;

#include <chrono>

#include <numeric>

#include <vector>
using std::vector;

#include <complex>
using std::complex;

template<>
class std::formatter<complex<float>>{
public:
  constexpr auto parse( std::format_parse_context& ctx ) {
    return ctx.begin(); };
  auto format( const complex<float>& z,std::format_context& ctx ) const {
    return std::format_to
      ( ctx.out(),"({},{})",z.real(),z.imag());
  };
};

template<>
class std::formatter<complex<double>>{
public:
  constexpr auto parse( std::format_parse_context& ctx ) {
    return ctx.begin(); };
  auto format( const complex<double>& z,std::format_context& ctx ) const {
    return std::format_to
      ( ctx.out(),"({},{})",z.real(),z.imag());
  };
};

int main() {

  int N;
  cin >> N;

  using myclock = std::chrono::high_resolution_clock ;

  using namespace std::complex_literals;
  vector<complex<double>>
    vec1( N, 1.+2.5i );
  auto vec2( vec1 );

  /*
   * prep data
   */
  for ( int i=0; i<vec1.size(); ++i ) {
    vec2[i] *= vec1[i];
  }

  /*
   * Now actual timing
   */
  auto start_time = myclock::now();
  for ( int i=0; i<vec1.size(); ++i ) {
    vec2[i] = vec1[i] * ( 1.+1.i );
  }
  auto duration = myclock::now()-start_time;
  auto nanosec_duration =
    std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
  auto usec = nanosec_duration.count();
  auto Gflops = 6.*N / usec;

  cout << "Time\n";
  cout << "usec: " << usec << "; Gflops: " << Gflops << '\n';
  cout << "time\n";

  cout << "Sum\n";
  auto sum = accumulate
    ( vec2.begin(),vec2.end(),
      complex<double>(0.) );
  println( "result: {}",sum );
  cout << "sum\n";

  if (sum==complex<double>(0.)) cout << '\n';

  return 0;
}
