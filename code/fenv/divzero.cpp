#include <iostream>
using std::cin,std::cout;

#include <cfenv>

int main() {
  std::feclearexcept(FE_ALL_EXCEPT);
  float zero;
  cin >> zero;

  //codesnippet fenvdivbyzero
  float result = 1.f/zero;
  cout << "result: " << result << '\n';
  if (std::fetestexcept(FE_DIVBYZERO))
    std::cout << "division by zero reported\n";
  else
    std::cout
      << "division by zero not reported\n";
  //codesnippet end

  return 0;
}
