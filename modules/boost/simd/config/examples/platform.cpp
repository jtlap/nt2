#include <iostream>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/config/os.hpp>

int main()
{
  #if defined(BOOST_SIMD_OS)
  std::cout << "Current OS : " << BOOST_SIMD_OS << std::endl;
  #endif
}


