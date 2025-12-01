/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** implimpl.cxx : simple implementation module
 ****
 ****************************************************************/

// implementation unit, nothing exported
module module_with_intface;
// function to be exported by the interface
int f( int i ) { return i/2; };

