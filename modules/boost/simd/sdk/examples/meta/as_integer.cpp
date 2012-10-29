#include <boost/mpl/assert.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::simd::int32_t;
using boost::simd::uint32_t;
using boost::is_same;
using boost::simd::pack;

int main()
{
  BOOST_MPL_ASSERT(( is_same<int32_t,       boost::dispatch::meta::as_integer<float>::type>            ));
  BOOST_MPL_ASSERT(( is_same<uint32_t,      boost::dispatch::meta::as_integer<float, unsigned>::type>  ));
  BOOST_MPL_ASSERT(( is_same<int32_t,       boost::dispatch::meta::as_integer<uint32_t, signed>::type> ));
  BOOST_MPL_ASSERT(( is_same<pack<int32_t>, boost::dispatch::meta::as_integer< pack<float> >::type>    ));
}
