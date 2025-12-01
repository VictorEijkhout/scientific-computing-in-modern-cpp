/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** cxxn.cxx : simple example of cxxopts
 ****
 ****************************************************************/

#include <iostream>
using std::cin, std::cout;

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "cxxopts.hpp"

int main(int argc,char **argv) {

  cxxopts::Options options
    ("cxxopts",
     "Commandline options demo");
  options.add_options()
    ("n,ntimes","number of times",
     cxxopts::value<int>()
     ->default_value("37")
     )
    ("h,help","usage information")
    ;
  auto result = options.parse(argc, argv);
  if (result.count("help")>0) {
    cout << options.help() << '\n';
    return 0;
  }
  auto number_of_times = result["ntimes"].as<int>();
  cout << "number of times: "
       << number_of_times << '\n';

  return 0;
}
