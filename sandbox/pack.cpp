#include <iostream>
//#define BOOST_PROTO_STRICT_RESULT_OF

#include <nt2/sdk/simd/pack.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/sin.hpp>

using namespace std;

int main()
{
  NT2_ALIGNED_TYPE(float) v[4] = { 4.5,3.4,3.2,2.1};
  nt2::simd::pack<float> x,y(5.321),w(&v[0],0);
  std::cout << y << "\n";
  std::cout << w << "\n";
  x = y+y;
  std::cout << x << "\n";
  x = y*1000;
  std::cout << x << "\n";
  x = nt2::cos(y)*nt2::cos(y) + nt2::sin(y)*nt2::sin(y);
  std::cout << x << "\n";
}
