#include <boost/simd/memory/align_on.hpp>

int main()
{
  using boost::simd::align_on;

  // Align an integral value on the default SIMD compatible alignment
  std::size_t v = align_on(13);

  // Align a pointer on  the default SIMD compatible alignment
  short s;
  short* x = align_on(&s);
}
