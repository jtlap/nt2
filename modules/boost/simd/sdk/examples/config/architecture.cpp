#include <iostream>
#include <boost/simd/sdk/config/arch.hpp>

int main()
{
  #ifdef BOOST_SIMD_ARCH
  std::cout << "Current architecture      : " << BOOST_SIMD_ARCH           << std::endl;
  std::cout << "Current memory alignement : " << BOOST_SIMD_ARCH_ALIGNMENT << std::endl;
  #endif
}
