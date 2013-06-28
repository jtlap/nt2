#include <iostream>
#include <boost/simd/memory/align_on.hpp>

int main()
{
  // Align an integral value
  std::cout << 10 << " -> " << boost::simd::align_on(10, 16) << std::endl;

  // Align a pointer value
  char s;
  std::cout << (void*)&s << " -> " << (void*)boost::simd::align_on(&s, 16) << std::endl;
}
