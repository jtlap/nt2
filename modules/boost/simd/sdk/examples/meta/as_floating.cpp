#include <boost/mpl/assert.hpp>
#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::simd::int32_t;
using boost::simd::uint32_t;
using boost::simd::uint64_t;
using boost::is_same;
using boost::simd::pack;

int main()
{
  BOOST_MPL_ASSERT(( is_same<float,       boost::dispatch::meta::as_floating<int32_t>::type>         ));
  BOOST_MPL_ASSERT(( is_same<float,       boost::dispatch::meta::as_floating<uint32_t>::type>        ));
  BOOST_MPL_ASSERT(( is_same<double,      boost::dispatch::meta::as_floating<uint64_t>::type>        ));
  BOOST_MPL_ASSERT(( is_same<pack<float>, boost::dispatch::meta::as_floating<pack<int32_t> >::type> ));
}
