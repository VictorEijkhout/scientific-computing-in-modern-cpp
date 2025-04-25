/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** print.cxx : print through overloaded format
 ****
 ****************************************************************/

#include <iostream>
using std::cin, std::cout;
#include <print>
using std::println;

#include <complex>
using std::complex;

//codesnippet printcomplexfloat
template<>
class std::formatter<complex<float>>{
public:
  constexpr auto parse( std::format_parse_context& ctx ) {
    return ctx.begin(); };
  auto format( const complex<float>& z,std::format_context& ctx ) const {
    return std::format_to
      ( ctx.out(),"({},{})",z.real(),z.imag());
  };
};
//codesnippet end

template<>
class std::formatter<complex<double>>{
public:
  constexpr auto parse( std::format_parse_context& ctx ) {
    return ctx.begin(); };
  auto format( const complex<double>& z,std::format_context& ctx ) const {
    return std::format_to
      ( ctx.out(),"({},{})",z.real(),z.imag());
  };
};

int main() {

  cout << "Def\n";
  //codesnippet complexdef
  complex<double> d(1.,3.);
  println("{}",d);
  complex<float> f;
  f.real(1.); f.imag(2.);
  println("{}",f);
  //codesnippet end
  cout << " .. def\n";
  
  cout << "Ops\n";
  //codesnippet complexops
  using namespace std::complex_literals;
  auto e = d*2.;
  println("{}",e); 
  auto g = e + 2.5i + 3.; // note 3dot
  println("{}",g); 
  //codesnippet end
  cout << " .. ops\n";

  return 0;
}

