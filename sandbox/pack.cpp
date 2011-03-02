#include <iostream>
//#define BOOST_PROTO_STRICT_RESULT_OF

#include <nt2/sdk/simd/pack.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/sin.hpp>

using namespace std;

int main()
{
  nt2::simd::pack<float> x,y(5.321);
  std::cout << y << "\n";
  x = y+y;
  std::cout << x << "\n";
  x = y*1000;
  std::cout << x << "\n";
  x = nt2::cos(y)*nt2::cos(y) + nt2::sin(y)*nt2::sin(y);
  std::cout << x << "\n";
}
