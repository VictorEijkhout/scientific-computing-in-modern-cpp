/****************************************************************
 ****
 **** This program source is part of
 **** Introduction to High-performance Scientific Computing
 **** by Victor Eijkhout
 **** copyright Victor Eijkhout 2011-2025
 ****
 **** hello.cxx : gdb example program for int overflow
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
#include <format>
using std::format;
#include <print>
using std::println;

//codesnippet gdbshort
void say(short int n) {
  println
    ("hello world {}",n);
}

int main() {

  for (short i=0; ; i+=20) {
    short ii;
    ii = i*i;
    ++i;
    say(ii);
  }

  return 0;
}
//codesnippet end
