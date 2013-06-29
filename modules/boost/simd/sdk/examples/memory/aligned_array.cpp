#include <boost/simd/memory/aligned_array.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/assert.hpp>

int main()
{
  boost::simd::aligned_array<float,16> x;
  BOOST_ASSERT( boost::simd::is_aligned(&x[0],16) );

  for(std::size_t i=0;i<x.size();++i)
    x[i] = 1.f+i;
}
