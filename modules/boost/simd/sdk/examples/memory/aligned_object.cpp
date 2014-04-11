#include <boost/simd/memory/aligned_object.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/assert.hpp>

class foo : public boost::simd::aligned_object<16>
{
  public:
  int  member;
};

int main()
{
  foo* ptr = new foo;

  BOOST_ASSERT( boost::simd::is_aligned(ptr,16) );

  delete ptr;
}
