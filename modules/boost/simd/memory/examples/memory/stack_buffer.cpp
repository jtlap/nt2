#include <boost/simd/memory/stack_buffer.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/assert.hpp>

int main()
{
  BOOST_SIMD_STACK_BUFFER(data, float, 7);

  BOOST_ASSERT( boost::simd::is_aligned(&data[0],BOOST_SIMD_ALLOCA_ALIGNMENT) );
}
