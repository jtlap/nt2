#include <boost/simd/preprocessor/stack_buffer.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/assert.hpp>

int main()
{
  BOOST_SIMD_SCOPED_STACK_BUFFER(data, float, 7);
}
