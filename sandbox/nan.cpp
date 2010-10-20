#include <iostream>
#include <nt2/sdk/simd/pack.hpp>

using namespace nt2;

int main()
{
  simd::pack<float> x,y;
  x = x + y;
}
