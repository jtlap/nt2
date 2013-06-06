#include <boost/simd/memory/is_aligned.hpp>
#include <boost/assert.hpp>

int main()
{
  BOOST_ASSERT(  boost::simd::is_aligned(   0 , 4 ) );
  BOOST_ASSERT(  boost::simd::is_aligned(  12 , 4 ) );
  BOOST_ASSERT( !boost::simd::is_aligned(   1 , 4 ) );
  BOOST_ASSERT( !boost::simd::is_aligned(1337 , 4 ) );
}
