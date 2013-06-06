#include <boost/simd/memory/align_on.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/assert.hpp>

int main()
{
  std::size_t v = boost::simd::align_on(13, 4);
  BOOST_ASSERT( boost::simd::is_aligned(v,4) );

  short s;
  short* x = boost::simd::align_on(&s, 8);
  BOOST_ASSERT( boost::simd::is_aligned(x,8) );
}
