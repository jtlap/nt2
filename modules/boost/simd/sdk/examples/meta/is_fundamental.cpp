#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/is_fundamental.hpp>
#include <boost/simd/sdk/simd/pack.hpp>

using boost::dispatch::meta::is_fundamental;
using boost::simd::pack;

int main()
{
  BOOST_MPL_ASSERT    (( is_fundamental<bool>        ));
  BOOST_MPL_ASSERT    (( is_fundamental<int>         ));
  BOOST_MPL_ASSERT_NOT(( is_fundamental<int*>        ));
  BOOST_MPL_ASSERT_NOT(( is_fundamental< pack<int> > ));
}
