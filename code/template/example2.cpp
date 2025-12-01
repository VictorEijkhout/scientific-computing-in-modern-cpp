/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2021-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
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
  Store(T v);
  T value() const;
  Store copy() const;
  Store<T> negative() const;
};

int main() {

  Store<int> i5(5);
  cout << i5.value() << '\n';

  Store<float> f314(3.14);
  cout << f314.value() << '\n';

  Store<float> also314 = f314.copy();
  cout << also314.value() << '\n';

  return 0;
}

template< typename T >
Store<T>::Store(T v) : stored(v) {};

template< typename T >
T Store<T>::value() const { return stored;};

template< typename T >
Store<T>  Store<T>::copy() const { return Store<T>(stored); };

template< typename T >
Store<T> Store<T>::negative() const { return Store<T>(-stored); };
