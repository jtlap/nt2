#include <iostream>
#include <boost/simd/sdk/memory/is_aligned.hpp>

using boost::simd::memory::is_aligned;

int main()
{
  std::cout << std::boolalpha << is_aligned<4>(0)     << std::endl;
  std::cout << std::boolalpha << is_aligned<4>(1)     << std::endl;
  std::cout << std::boolalpha << is_aligned<4>(12)    << std::endl;
  std::cout << std::boolalpha << is_aligned<4>(1337)  << std::endl;
}
