#include <iostream>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/memory/align_on.hpp>

using boost::simd::align_on;

int main()
{
  std::cout << align_on<4>(0)     << std::endl;
  std::cout << align_on<4>(1)     << std::endl;
  std::cout << align_on<4>(11)    << std::endl;
  std::cout << align_on<4>(1337)  << std::endl;
}
