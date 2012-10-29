#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/is_unspecified.hpp>
#include <boost/simd/sdk/simd/pack.hpp>

using boost::dispatch::meta::is_unspecified;
using boost::simd::pack;

struct test {};

int main()
{
  BOOST_MPL_ASSERT_NOT(( is_unspecified<bool>        ));
  BOOST_MPL_ASSERT_NOT(( is_unspecified<int>         ));
  BOOST_MPL_ASSERT_NOT(( is_unspecified<int*>        ));
  BOOST_MPL_ASSERT_NOT(( is_unspecified< pack<int> > ));
  BOOST_MPL_ASSERT    (( is_unspecified<test>        ));
}
