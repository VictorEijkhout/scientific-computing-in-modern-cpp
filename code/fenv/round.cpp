#include <iostream>
using std::cin,std::cout;

#include <cfenv>

int main() {
  std::feclearexcept(FE_ALL_EXCEPT);
  float one;
  cin >> one;

  fesetround(FE_UPWARD);
  float thirdup = one/3.f;
  fesetround(FE_DOWNWARD);
  float thirddn = one/3.f;
  cout << "difference: "
       << thirdup-thirddn << '\n';


  return 0;
}
