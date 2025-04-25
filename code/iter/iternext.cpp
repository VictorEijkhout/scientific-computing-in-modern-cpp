/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2019-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** iter.cxx : tinkering with iterators
 ****
 ****************************************************************/

#include <iostream>
using std::cout;

#include <iterator>

#include <vector>
using std::vector;

#include <memory>
using std::shared_ptr;

#include <cassert>

int main() {

  {
    cout << "PlusMinus\n";
    //codesnippet iterplusminusnext
    vector<int> counts{1,2,3,4};
    auto second = counts.begin();
    second = std::next(second);
    cout << "Second element: " << *second << '\n';
    auto last = counts.end();
    last = std::prev(last);
    cout << "Last element: " << *last << '\n';
    //codesnippet end
    cout << "plusminus\n";
  }

  return 0;
}
