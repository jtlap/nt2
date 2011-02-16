#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/is_fundamental.hpp>
#include <nt2/sdk/simd/pack.hpp>

using nt2::meta::is_fundamental;
using nt2::simd::pack;

int main()
{
  BOOST_MPL_ASSERT    (( is_fundamental<bool>        ));
  BOOST_MPL_ASSERT    (( is_fundamental<int>         ));
  BOOST_MPL_ASSERT_NOT(( is_fundamental<int*>        ));
  BOOST_MPL_ASSERT_NOT(( is_fundamental< pack<int> > ));
}
