#include <iostream>
#include <boost/simd/include/functions/bitwise_cast.hpp>

int main()
{
  float f = -1.f;
  std::cout << std::hex << boost::simd::bitwise_cast<unsigned int>(f) << "\n";
}
