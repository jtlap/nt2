#include <boost/simd/preprocessor/new.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/assert.hpp>

struct foo
{
  BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(8);
};

int main()
{
  foo* p = new foo;

  BOOST_ASSERT( boost::simd::is_aligned(p,8) );
}
