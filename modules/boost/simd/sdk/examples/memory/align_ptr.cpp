#include <boost/simd/memory/align_ptr.hpp>
#include <boost/assert.hpp>

int main()
{
  float q;
  BOOST_ASSERT(&q == boost::simd::align_ptr<sizeof(float)>(&q));
}
