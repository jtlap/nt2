#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <iostream>

int main()
{
  using boost::simd::bitwise_cast;

  std::cout << std::hex
            << bitwise_cast<int>( 1.f )           << " "
            << bitwise_cast<float>( 0x3F800000 )  << "\n";
}
