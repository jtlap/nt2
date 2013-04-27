#include <boost/simd/memory/align_on.hpp>

int main()
{
  using boost::simd::align_on;

  // Align an integral value on 4
  std::size_t u = align_on(11,4);

  // Align a pointer on 8
  float f;
  float* w = align_on(&f,8);
}
