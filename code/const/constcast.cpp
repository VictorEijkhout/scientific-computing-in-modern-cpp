/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** constproblem.cxx : illustrating the const problem
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
#include <vector>
using std::vector;

void old_c_routine( float*in,float*out );
void new_cpp_routine( const vector<float>&in, vector<float>&out ) {
  old_c_routine
    ( const_cast<float*>( in.data() ), out.data() );
};

int main() {  
  return 0;
}

void old_c_routine( float*,float* ) {};
