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

#include <format>
using std::format;
#include <vector>
using std::vector;

#include <chrono>
using Clock = std::chrono::high_resolution_clock ;
#include "clock.hpp"
#include "allocation.hpp"

#include "cxxopts.hpp"

using floattype = double;

int main(int argc,char ** argv) {

  cxxopts::Options options("stride", "Decrease performance with increasing stride");
  options.add_options()
    ("a,associativity","attempted values",
         cxxopts::value< vector<int> >()->default_value("8,9,10,11,12,13,14") )
    ("d,displacement","stride (in KiByte) by any other name",
         cxxopts::value<int>()->default_value("4") )
    ("r,repeat", "how many repeats",
         cxxopts::value<int>()->default_value("1000"))
    ("t,trace", "print trace output")
    ("h,help","usage information")
    ;
  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    cout << format("{}\n",options.help());
    return 1;
  }

  auto associativity = result["a"].as<vector<int>>();
  auto displacement_in_kib  = result["d"].as<int>();
  auto displacement_in_bytes = displacement_in_kib * 1024;
  auto displacement_in_words = displacement_in_bytes / sizeof(floattype);
  int how_many_repeats = result["r"].as<int>();
  bool tracing = result.count("trace");

  cout << format("Repeats: {}\n",how_many_repeats);

  clock_init();
  int microsec_reference;
  for (int assoc : associativity ) {

    std::cout << std::format("Associativity: {}\n",assoc);

    auto datasize_in_bytes = displacement_in_bytes * assoc;
    auto datasize_in_words = datasize_in_bytes / sizeof(floattype);
    auto words_accessed = how_many_repeats * assoc;
    if (tracing) 
      cout << format("Stride bytes={}, words={} and assoc={} => data in words {}\n",
                     displacement_in_bytes,displacement_in_words,assoc,
                     datasize_in_words);
    Cache<floattype> write_data(datasize_in_words);
    write_data
      .trace(tracing)
      .multiplex(1)
      .align(4096)
      .allocate();

    /*
     * Timed kernel
     */
    int microsec_duration;
    {
      auto start_time = Clock::now();
      auto data = write_data.get_stream().data();
      for ( int irepeat=0; irepeat<how_many_repeats; ++irepeat )
        for ( int loc=0; loc<data.size(); loc+=displacement_in_words )
          data[loc] += loc;
      microsec_duration = compute_microsec_duration(start_time);
    }
        // my_data_stream.transform_in_place
        //   ( [] (floattype& x ) { x+=1.; }, ,how_many_repeats );
    if (tracing)
      cout << format(" .. ran for {} usec\n",microsec_duration);

    /*
     * Timing processing
     */
    auto [report_string,nsec_per_word] =
      report_time_per_word(microsec_duration,words_accessed);
    cout << format("Time/access: {:.3} nsec\n",nsec_per_word);

  }

  return 0;
}
