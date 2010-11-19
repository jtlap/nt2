#include <iostream>
#include <nt2/sdk/simd/pack.hpp>
#include <nt2/include/functions/sqr.hpp>

using namespace std;

int main()
{
  nt2::simd::pack<float> x(3);

  cout << x << "\n";
  cout << x*x << "\n";
  cout << x*(x+x) << "\n";
  cout << nt2::sqr(x+x) << "\n";
  cout << nt2::sqr(x+x)+x*x << "\n";
  cout << (nt2::sqr(x*x)+x*x)/x << "\n";
}
