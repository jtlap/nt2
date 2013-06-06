#include <boost/simd/preprocessor/aligned_type.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/assert.hpp>

int main()
{
  BOOST_SIMD_ALIGNED_TYPE_ON(char, 8)  x[3];
  BOOST_SIMD_ALIGNED_TYPE_ON(float,8)  y;

  BOOST_ASSERT( boost::simd::is_aligned(&x[0],8) );
  BOOST_ASSERT( boost::simd::is_aligned(&y,8) );
}
