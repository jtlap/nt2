#include <boost/simd/preprocessor/malloc.hpp>
#include <cstddef>
#include <cstdlib>

BOOST_SIMD_MALLOC void* my_malloc(std::size_t n)
{
  return malloc(n);
}

int main()
{
  void* q = my_malloc(7);
  free(q);
}
