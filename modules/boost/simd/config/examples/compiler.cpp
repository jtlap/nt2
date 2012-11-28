#include <iostream>
#include <boost/simd/sdk/config/compiler.hpp>

int main()
{
  #if defined( BOOST_SIMD_COMPILER )
  std::cout << "Current compiler : " << BOOST_SIMD_COMPILER << std::endl;
  #endif
}

