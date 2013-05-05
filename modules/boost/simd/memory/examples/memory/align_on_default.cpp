#include <boost/simd/memory/align_on.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/assert.hpp>

int main()
{
  std::size_t v = boost::simd::align_on(13);
  BOOST_ASSERT( boost::simd::is_aligned(v) );

  short s;
  short* x = boost::simd::align_on(&s);
  BOOST_ASSERT( boost::simd::is_aligned(x) );
}
