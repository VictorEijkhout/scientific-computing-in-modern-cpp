/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2025
 ****
 **** Programs for hardware exploration
 ****
 **** bandwidth.cpp : saturation by multi-threading
 ****
 ****************************************************************/

#include <iostream>
using std::cout, std::cin, std::endl;
#include <sstream>
using std::stringstream;
#include <format>
using std::format;

#include <vector>
using std::vector;

#include "clock.hpp"
#include "allocation.hpp"

#include <cstdint>

#include "omp.h"
#include "cxxopts.hpp"

using real = double;

int main(int argc,char **argv) {

  cxxopts::Options options("bandwidth", "Saturate bandwidth through streaming threads");
  options.add_options()
    ("k,kilobyte", "data size in kbyte",    cxxopts::value<int>()->default_value("32"))
    ("i,iterations","repeats for averaging",cxxopts::value<int>()->default_value("100"))
    ("t,trace","tracing",cxxopts::value<bool>()->default_value("false"))
    ("h,help","usage information")
    ;
  auto result = options.parse(argc, argv);
  if (result.count("help")) {
    std::cout << options.help() << '\n';
    return 1;
  }

  const int nthreads =
    [] () {
    int nthreads;
#pragma omp parallel
#pragma omp master
    nthreads = omp_get_num_threads();
    return nthreads; } ();
  cout << format("Threads: {}\n",nthreads);

  /*
   * Create cache data
   */
  auto trace = result["trace"].as<bool>();
  int how_many_repeats = result["iterations"].as<int>();
  auto storage = 
    [=] () {
    uint64_t memorysize_in_bytes = static_cast<uint64_t>(1024)*result["k"].as<int>();
    auto memorysize_in_words_per_thread = memorysize_in_bytes/sizeof(real);
    cout << "Data size in words (each thread): "
        << human_size(memorysize_in_words_per_thread)
        << " , repetitions: " << how_many_repeats
        << '\n';
    auto cache= Cache<real>( memorysize_in_words_per_thread,nthreads,trace );
    cache.set( static_cast<real>(1.) );
    return cache;
  }();

  /*
   * Timed kernel
   */
  clock_init();
  try {
    auto start_time = Clock::now();
    vector<std::uintptr_t> offsets(nthreads);
    vector<real> results(nthreads,0.);
    float bw{0};
    uint64_t data_stream_size{0};
#pragma omp parallel proc_bind(spread) reduction(+:bw)
    {
      int my_thread_number = omp_get_thread_num();
      std::span<real> thread_data_stream = storage.get_stream(my_thread_number);
      offsets.at(my_thread_number) = reinterpret_cast<std::uintptr_t>( thread_data_stream.data() ); //snippetskip
#pragma omp single //snippetskip
      data_stream_size = thread_data_stream.size(); //snippetskip
      for (int irepeat=0; irepeat<how_many_repeats; ++irepeat) {
	results.at(my_thread_number) += sum_stream(thread_data_stream);
      }
      bw += how_many_repeats * thread_data_stream.size()*sizeof(real);
    }
    int microsec_duration = compute_microsec_duration(start_time);
    cout << format("runtime: {} msec\n",microsec_duration);
    float bandwidth_in_gig_per_sec = ( bw * 1.e-9 ) / ( microsec_duration * 1.e-6 );
    cout << format("Bandwidth Gbyte/sec: {}\n",bandwidth_in_gig_per_sec);
    cout << format("per thread: {}\n",bandwidth_in_gig_per_sec/nthreads);
    /*
     * Sanity checks
     */
    auto o0 = offsets.at(0);
    for ( auto& o : offsets ) o -= o0;
    // for ( auto o : offsets )
    //   cout << o/sizeof(real) << " "; cout << '\n';
    cout << format("sum: {} s/b {}\n",
		   [results] () { real total_sum{0.};
		     for ( auto t : results ) total_sum += t;
		     return total_sum; } (),
		   how_many_repeats*data_stream_size*nthreads);

  } catch ( std::string s ) {
    cout << s << '\n'; return 1;
  } catch ( ... ) {
    cout << "other exception\n"; return 1;
  }
  /*
   * Prevent compiler optimization
   */
  storage.force();

  return 0;
}
