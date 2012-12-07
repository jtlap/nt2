#include <iostream>
#include <boost/simd/sdk/memory/is_aligned.hpp>

using boost::simd::is_aligned;

int main()
{
  std::cout << std::boolalpha << is_aligned(0,4)     << std::endl;
  std::cout << std::boolalpha << is_aligned(1,4)     << std::endl;
  std::cout << std::boolalpha << is_aligned(12,4)    << std::endl;
  std::cout << std::boolalpha << is_aligned(1337,4)  << std::endl;
}
