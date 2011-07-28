#include <iostream>
#include <boost/simd/sdk/config/os.hpp>

int main()
{
  #ifdef BOOST_SIMD_OS_DETECTED
  std::cout << "Current OS : " << BOOST_SIMD_OS_STRING << std::endl;
  #endif
}


