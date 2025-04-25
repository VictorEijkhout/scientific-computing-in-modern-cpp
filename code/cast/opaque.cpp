/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2018-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** opaque.cpp : opaque handles
 ****
 ****************************************************************/

#include <iostream>
using namespace std; //::static_cast;

//codesnippet opqfun
void f( void *p,int type ) {
  if (type==1) {
    int *i = static_cast<int*>(p);
    cout << i << '\n';
  } // other cases omitted
}
//codesnippet end

int main() {

  //codesnippet opqmain
  int i=5;
  f( (void*)(&i),1 );
  float f=.5;
  f( (void*)(&f),2 );
  //codesnippet end
  
  return 0;
}
