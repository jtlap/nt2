#include <boost/simd/memory/config.hpp>
#include <cstddef>
#include <cstdlib>

BOOST_SIMD_MALLOC void* my_malloc(std::size_t n)
{
  return malloc(n);
}

int main()
{
  float* q = my_malloc(7);

  free(q);
}
