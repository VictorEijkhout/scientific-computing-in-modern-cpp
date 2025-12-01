/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** implementation.cxx : trying to hack an implementation of smart pointers
 ****
 ****************************************************************/

#include <iostream>
using std::cout;

class HasY {
private:
  double y;
public:
  HasY() = delete;
  HasY( double y) : y(y) {};
  auto& value() { return y; }
};

class ReferenceCounter {
private:
  unsigned int count_{1};
public:
  auto& count() { return count_; };
};

template<typename T>
class SmartPointer {
private:
  T* data_;
  ReferenceCounter *count_;
public:
  SmartPointer( T* data);
  ~SmartPointer();
  SmartPointer( const SmartPointer<T>& sp );
  T* operator->();
  auto count() { return count_->count(); };
};

template<typename T>
SmartPointer<T>::SmartPointer( T* data)
  : data_(data),count_( new ReferenceCounter ) {};

template<typename T>
SmartPointer<T>::SmartPointer( const SmartPointer<T>& sp )
  : data_(sp.data_),count_(sp.count_) {
  cout << "calling copy constructor\n";
  count_->count()++;
};

template<typename T>
SmartPointer<T>::~SmartPointer() {
  count_->count()--;
  if (count_->count()==0) {
    cout << "final delete\n";
    delete data_; delete count_;
  } else cout << "ref count lower only\n";
};

template<typename T>
T* SmartPointer<T>::operator->() {
  return data_;
};

int main() {
  auto y = SmartPointer<HasY>( new HasY(3.7) );

  cout << "Reference count of new object: " << y.count() << '\n';
  cout << "value: " << y->value() << '\n';

  SmartPointer<HasY> z = y;

  cout << "New object reference count: " << z.count()
       << ", value " << z->value() << '\n';
  return 0;
}

#if 0
  SmartPointer<T> operator=( const SmartPointer<T>& sp ) {
    cout << "calling copy assignment constructor\n";
    SmartPointer<T> newptr{ sp.data_,sp.count_ };
    count_->count()++;
    return newptr;
  };
#endif
