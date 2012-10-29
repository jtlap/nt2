#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/is_signed.hpp>
#include <boost/simd/sdk/simd/pack.hpp>

using boost::dispatch::meta::is_signed;

using boost::simd::pack;

int main()
{
  BOOST_MPL_ASSERT_NOT(( is_signed<unsigned int> ));
  BOOST_MPL_ASSERT    (( is_signed<int>          ));
  BOOST_MPL_ASSERT_NOT(( is_signed<bool>         ));
  BOOST_MPL_ASSERT    (( is_signed<float>        ));
  BOOST_MPL_ASSERT    (( is_signed< pack<int> >  ));
}
