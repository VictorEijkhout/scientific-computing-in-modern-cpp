/****************************************************************
 ****
 **** This program source is part of
 **** Introduction to High-performance Scientific Computing
 **** by Victor Eijkhout
 **** copyright Victor Eijkhout 2011-2024
 ****
 **** gdb example program
 ****
 ****************************************************************/

#include <format>
using std::format;
#include <iostream>
using std::cout;
#include <print>
using std::println;

void say(int n) {
  println("hello world {}",n);
}

int main() {

  for (int i=0; i<10; ++i) {
    int ii;
    ii = i*i;
    ++ii;
    say(ii);
  }

  return 0;
}
  
