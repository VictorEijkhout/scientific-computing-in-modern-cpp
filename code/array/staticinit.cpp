/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2018-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** staticinit.cxx : initialization of static arrays
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <print>
using std::println;

#include <vector>
using std::vector;

int main() {

  {
    int numbers[] = {5,4,3,2,1};
    println("{}",numbers[3]);
  }
  {
    int numbers[5]{5,4,3,2,1};
    numbers[3] = 21;
    println("{}",numbers[3]);
  }
  

  return 0;
}
