/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2021-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** example.cxx : nonsense example to see things in action
 ****
 ****************************************************************/

#include <iostream>
using std::cout;

template< typename T >
class Store {
private:
  T stored;
public:
  Store(T v) : stored(v) {};
  T stored_value() { return stored;};
  // spell out the template parameter
  Store<T> copy() const { return Store<T>(stored); };
  // using CTAD:
  Store negative() const { return Store(-stored); };
};

int main() {

  cout << "StoreI5\n";
  Store<int> i5(5);
  cout << i5.stored_value() << '\n';
  cout << "storei5\n";

  Store<float> f314(3.14);
  cout << f314.stored_value() << '\n';

  cout << "StoreF314\n";
  Store<float> also314 = f314.copy();
  cout << also314.stored_value() << '\n';
  Store<float> min314 = f314.negative();
  cout << min314.stored_value() << '\n';
  cout << "storef314\n";

  return 0;
}

