/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2020 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** the C++ random number generator
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#include <random>

int main() {

  // seed the generator
  std::random_device r;
  // set the default random number generator
  std::default_random_engine generator{r()};
  // distribution: real between 0 and 1
  std::uniform_real_distribution<float> distribution(0.,1.);

  for ( int i=0; i<5; i++)
    cout << "random: "
         << distribution(generator)
         << '\n';

  return 0;
}
