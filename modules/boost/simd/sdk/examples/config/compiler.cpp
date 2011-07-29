#include <iostream>
#include <boost/simd/sdk/config/compiler.hpp>

int main()
{
  #ifdef BOOST_SIMD_COMPILER_DETECTED
  std::cout << "Current compiler : " << BOOST_SIMD_COMPILER_STRING << std::endl;
  #endif
}

