#include <iostream>
using std::cout;
#include "instantlib.h"

template< typename T >
void instant<T>::out() { cout << "hello\n"; };

template class instant<char>;
template class instant<int>;
