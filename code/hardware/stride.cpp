/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2024
 ****
 **** Programs for hardware exploration
 ****
 **** stride.cxx : measure nsec / word for different strides, sequential
 ****
 ****************************************************************/

#include <iostream>
using std::cout, std::cin, std::endl;

#include <vector>
using std::vector;

// #include "fmt/format.h"
// using fmt::print;
#include <format>
using std::format;

#include "clock.hpp"
#include "allocation.hpp"

#include "cxxopts.hpp"
#include "omp.h"

using floattype = double;

int main(int argc,char ** argv) {

  cxxopts::Options options("stride", "Decrease performance with increasing stride");
  options.add_options()
    ("A,access", "number of kwords accessed",   cxxopts::value<int>())
    ("D,dataset","dataset in kwords",           cxxopts::value<int>())
    ("f,flush","flush cache between passes")
    ("r,repeat", "how many repeats",
         cxxopts::value<int>()->default_value("100"))
    ("s,stride", "strides (array)" ,
         cxxopts::value< vector<int> >()->default_value("1,2,3,4,5,6,7,8") )
    ("t,trace", "print trace output")
    ("h,help","usage information")
    ;
  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    cout << format("{}\n",options.help());
    return 1;
  }

  auto strides = result["s"].as< vector<int> >();
  int how_many_repeats = result["r"].as<int>();
  bool flush = result.count("flush");
  bool tracing = result.count("trace");

  cout << format("Repeats: {} flush: {}\n",how_many_repeats,flush);

  /*
   * OpenMP thread setup
   */
  const int nthreads =
    [] () {
    int nthreads;
#pragma omp parallel
#pragma omp master
    nthreads = omp_get_num_threads();
    return nthreads; } ();
  cout << format("Threads: {}\n",nthreads);

  clock_init();
  int microsec_reference;
  for (int stride : strides ) {

    cout << format("====\n");
    cout << format("Stride: {}\n",stride);

    auto [datasize_in_words,words_accessed] = 
      [result,stride] () {
        if (result.count("dataset")) {
          auto d = result["dataset"].as<int>() * 1024;
          return std::make_pair(d,d/stride);
        } else if (result.count("access")) {
          auto a = result["access"].as<int>() * 1024;
          return std::make_pair(a*stride,a);
        } else throw("Need either A/access or D/dataset option");
    }(); 
    cout << format(" .. dataset words: {}\n",human_size(datasize_in_words));
    Cache<floattype> write_data(datasize_in_words,nthreads,tracing);
    Cache<floattype> flush_data(datasize_in_words,nthreads,tracing);

    /*
     * Timed kernel
     */
    int microsec_duration;
    auto start_time = Clock::now();
    //codesnippet cachestridetest
    #pragma omp parallel proc_bind(spread)
    {
      int my_thread_number = omp_get_thread_num();
      auto my_data_stream = write_data.get_stream(my_thread_number);
      auto my_flush_stream = flush_data.get_stream(my_thread_number);
      for (int irepeat=0; irepeat<how_many_repeats; ++irepeat) {
        my_data_stream.transform_in_place( [] (floattype& x ) { x+=1.; }, stride );
        if (flush) //snipexclude
          my_flush_stream.transform_in_place( [] (floattype& x ) { x+=1.; }, stride );//snipexclude
      }
    }
    //codesnippet end
    microsec_duration = compute_microsec_duration(start_time);
    cout << format(" .. ran for {} usec\n",microsec_duration);

    /*
     * Timing processing
     */
    auto [report_string,nsec_per_word] = report_time_per_word(microsec_duration,words_accessed*how_many_repeats);
    cout << format("Time/access: {:} nsec\n",nsec_per_word);

  }

  return 0;
}
