#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/as_signed.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;
using boost::simd::pack;

int main()
{
  BOOST_MPL_ASSERT(( is_same<int       , boost::dispatch::meta::as_signed<unsigned int>::type>         ));
  BOOST_MPL_ASSERT(( is_same<int       , boost::dispatch::meta::as_signed<int>::type>                  ));
  BOOST_MPL_ASSERT(( is_same<float     , boost::dispatch::meta::as_signed<float>::type>                ));
  BOOST_MPL_ASSERT(( is_same< pack<int>, boost::dispatch::meta::as_signed< pack<unsigned int> >::type> ));
}
