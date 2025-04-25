/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2018-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** matvisit.cpp : applying visit to a matrix classes
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
#include <sstream>
using std::stringstream;

#include <string>
using std::string;

#include <variant>
using std::variant;
using std::visit;

class vector {};

//codesnippet visitmvp1
class sparse_matrix {
public:
  vector multiply( const vector& in ) const;
//codesnippet end
};

vector sparse_matrix::multiply( const vector& in ) const {
  cout << "sparse multiply\n";
  return in;
};

//codesnippet visitmvp2
class lowrank_matrix {
public:
  vector multiply( const vector& in ) const;
//codesnippet end
};

vector lowrank_matrix::multiply( const vector& in ) const {
  cout << "lowrank multiply\n";
  return in;
};

//codesnippet visitmvp3
class multiply_by {
private:
  const vector& in;
public:
  multiply_by( const vector& in ) : in(in) {};
  vector operator()( sparse_matrix m ) {
    return m.multiply(in); };
  vector operator()( lowrank_matrix m ) {
    return m.multiply(in); };
};
//codesnippet end

//codesnippet visitmvp5
template<class... Ts> struct overload
  : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...)
  -> overload<Ts...>;
//codesnippet end

int main() {

  //codesnippet visitmvp4
  variant<sparse_matrix,lowrank_matrix>
    this_is_sparse{ sparse_matrix{} },
    this_is_lowrank{ lowrank_matrix{} };

  vector invec;
  visit( multiply_by{invec},this_is_sparse );
  visit( multiply_by{invec},this_is_lowrank );
  //codesnippet end

  //codesnippet visitmvp6
  visit
    ( overload{
      [invec] ( const sparse_matrix& m ) {
        return m.multiply(invec); },
      [invec] ( const lowrank_matrix& m ) {
        return m.multiply(invec); }
      },
      this_is_sparse );
  //codesnippet end

  return 0;
}
