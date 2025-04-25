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

//codesnippet smartpointerhasy
class HasY {
private:
  double y;
public:
  HasY() = delete;
  HasY( double y) : y(y) {};
  auto& value() { return y; }
};
//codesnippet end

class ReferenceCounter {
private:
  unsigned int count_{1};
public:
  auto& count() { return count_; };
};

//codesnippet smartpointerconstruct
template<typename T>
class SmartPointer {
private:
  T* data_;
  ReferenceCounter *count_;
//codesnippet end
public:
  SmartPointer( T* data);
  ~SmartPointer();
  SmartPointer( const SmartPointer<T>& sp );
  T* operator->();
  auto count() { return count_->count(); };
};

//codesnippet smartpointerconstruct
template<typename T>
SmartPointer<T>::SmartPointer( T* data)
  : data_(data),count_( new ReferenceCounter ) {};
//codesnippet end

//codesnippet smartpointercopy
template<typename T>
SmartPointer<T>::SmartPointer( const SmartPointer<T>& sp )
  : data_(sp.data_),count_(sp.count_) {
  cout << "calling copy constructor\n";
  count_->count()++;
};
//codesnippet end

//codesnippet smartpointerdel
template<typename T>
SmartPointer<T>::~SmartPointer() {
  count_->count()--;
  if (count_->count()==0) {
    cout << "final delete\n";
    delete data_; delete count_;
  } else cout << "ref count lower only\n";
};
//codesnippet end

//codesnippet smartpointerget
template<typename T>
T* SmartPointer<T>::operator->() {
  return data_;
};
//codesnippet end

int main() {
  //codesnippet smartpointerconstruct
  auto y = SmartPointer<HasY>( new HasY(3.7) );
  //codesnippet end

  cout << "Reference count of new object: " << y.count() << '\n';
  cout << "value: " << y->value() << '\n';

  //codesnippet smartpointercopy
  SmartPointer<HasY> z = y;
  //codesnippet end

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
