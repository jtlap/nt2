#include <boost/simd/preprocessor/aligned_type.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/assert.hpp>

int main()
{
  BOOST_SIMD_ALIGNED_TYPE(char)   x[3];
  BOOST_SIMD_ALIGNED_TYPE(float)  y;

  BOOST_ASSERT( boost::simd::is_aligned(&x[0]) );
  BOOST_ASSERT( boost::simd::is_aligned(&y) );
}
