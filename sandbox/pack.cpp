#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/pack/io.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/constants/ten.hpp>
#include <iostream>

int main()
{
  boost::simd::pack<float> u /* = {4.64f} */, r;
  boost::simd::pack<int> v /*= {3}*/;

  r = nt2::tofloat(v);
  //std::cout << r << "\n";
  r = r + r;

#if 0
  r = u + nt2::tofloat(v);
  std::cout << r << "\n";

  r = nt2::tofloat(v+2)*nt2::Ten<boost::simd::pack<float> >();
  std::cout << r << "\n";
#endif
}
