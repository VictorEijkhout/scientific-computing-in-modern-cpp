/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2018-2021 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** spaced.cxx : namespaced enum
 ****
 ****************************************************************/

#include <iostream>
using namespace std;

class Field {
public:
  enum color { invalid=-1,white=0,red=1,blue=2,green=3 };
private:
  color mycolor;
public:
  void set_color( color c ) { mycolor = c; };
  color thecolor() { return mycolor; };
  bool valid_color() { return mycolor!=color::invalid; };
};

int main() {
  
  Field onefield;
  onefield.set_color( Field::color::blue );
  cout << "Color valid: " << boolalpha << onefield.valid_color() << '\n';
  onefield.set_color( Field::color::invalid );
  cout << "Color valid: " << boolalpha << onefield.valid_color() << '\n';

  return 0;
}
