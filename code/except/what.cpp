/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** what.cpp : get the what of std::exception objects
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
#include <vector>
using std::vector;

int main()
{

  for ( auto iexp : { 1,2,3 } ) {
    try {
      switch (iexp) {
        //codesnippet exceptwhat
      case 1 :
        [] (int s) { vector<int> x(s); }( -3 );
        break;
      //
      case 2 :
        [] (int s) { vector<int> x(3); x.at(s); }( 4 );
        break;
      //
      case 3 :
        [] () { throw(5); }();
        break;
        //codesnippet end
      default :
      cout << "Unknown experiment " << iexp << '\n';
      }
   } catch ( std::exception& e ) {
      cout << "For experiment " << iexp
           << " found standard exception: "
           << "\n  " << e.what() << '\n';
    } catch ( ... ) {
      cout << "For experiment " << iexp
           << " found unknown exception"
           << '\n';
    }      
  }

  return 0;

}
