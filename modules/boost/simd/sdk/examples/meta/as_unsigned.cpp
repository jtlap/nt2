#include <boost/mpl/assert.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::simd::pack;
using boost::is_same;

int main()
{
  BOOST_MPL_ASSERT(( is_same<unsigned int       , boost::dispatch::meta::as_unsigned<unsigned int>::type> ));
  BOOST_MPL_ASSERT(( is_same<unsigned int       , boost::dispatch::meta::as_unsigned<int>::type>          ));
  BOOST_MPL_ASSERT(( is_same<float              , boost::dispatch::meta::as_unsigned<float>::type>        ));
  BOOST_MPL_ASSERT(( is_same< pack<unsigned int>, boost::dispatch::meta::as_unsigned< pack<int> >::type>  ));
}
