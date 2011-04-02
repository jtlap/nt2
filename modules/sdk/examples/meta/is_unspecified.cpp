#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/is_unspecified.hpp>
#include <nt2/sdk/simd/pack.hpp>

using nt2::meta::is_unspecified;
using nt2::simd::pack;

struct test {};

int main()
{
  BOOST_MPL_ASSERT_NOT(( is_unspecified<bool>        ));
  BOOST_MPL_ASSERT_NOT(( is_unspecified<int>         ));
  BOOST_MPL_ASSERT_NOT(( is_unspecified<int*>        ));
  BOOST_MPL_ASSERT_NOT(( is_unspecified< pack<int> > ));
  BOOST_MPL_ASSERT    (( is_unspecified<test>        ));
}
