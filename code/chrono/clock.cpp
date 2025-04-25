/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** second.cxx : using chrono seconds
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
#include <iomanip>
using std::boolalpha;
#include <thread>

#include <chrono>
using namespace std::chrono;

int main() {

  //codesnippet clocksleep
  using myclock = system_clock;
  myclock::time_point before =
    myclock::now();
  // do something that takes time
  std::this_thread::sleep_for( 1.5s );//snippetexclude
  auto after = myclock::now();
  cout << "Action took: "
       << duration_cast<milliseconds>
            (after-before).count()
       << "ms\n";
  //codesnippet end

  return 0;
}
