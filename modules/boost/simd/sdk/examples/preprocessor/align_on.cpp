#include <boost/simd/preprocessor/align_on.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/assert.hpp>

int main()
{
  BOOST_SIMD_ALIGN_ON(8) float y;

  BOOST_ASSERT( boost::simd::is_aligned(&y, 8) );
}
