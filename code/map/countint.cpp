/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** countint.cxx : 
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
#include <print>
using std::println;

#include <map>
using std::map;

int main() {

  /*
   * Generate some numbers and store them in the map
   */
  map<int,int> intcount;
  for ( int i=0; i<16; i+=2) {
    int even = i%10;
    intcount[even] += 1;
  }

  /*
   * Iterate over all key/value pairs
   */
  for ( auto [num,count] : intcount ) {
    println("has {}, {} times",num,count);
  }

  /*
   * Test for existence of some keys
   */
  for ( auto k : {5,6} ) {
    println("key: {} appears {} times",k,intcount.count(k));
  }

  /*
   * Get the iterator of some keys that is present
   */
  //codesnippet intcountfind
  for ( auto k : {4,5} ) {
    auto wherek = intcount.find(k);
    if (wherek==intcount.end())
      println("could not find key {}",k);
    else {
      auto [kk,vk] = *wherek;
      println("found key: {}; has value {}",kk,vk);
    }
  }
  //codesnippet end

  return 0;
}
