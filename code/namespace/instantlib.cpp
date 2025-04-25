#include <iostream>
using std::cout;
#include "instantlib.h"

template< typename T >
void instant<T>::out() { cout << "hello\n"; };

//codesnippet instantc
template class instant<char>;
template class instant<int>;
//codesnippet end
