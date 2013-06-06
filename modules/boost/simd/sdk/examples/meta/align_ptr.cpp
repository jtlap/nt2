#include <boost/simd/meta/align_ptr.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>

int main()
{
  typedef boost::simd::meta::align_ptr<float>::type ptr_t;

  BOOST_MPL_ASSERT(( boost::is_same<ptr_t, float*>::type ));
}
