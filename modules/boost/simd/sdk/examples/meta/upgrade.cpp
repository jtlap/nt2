#include <boost/mpl/assert.hpp>
#include <boost/simd/sdk/config/types.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;
using boost::mpl::_;
using boost::dispatch::meta::upgrade;

using boost::simd::uint32_t;
using boost::simd::uint64_t;
using boost::simd::pack;

int main()
{
  BOOST_MPL_ASSERT(( is_same<uint32_t,        upgrade<uint16_t>::type>         ));
  BOOST_MPL_ASSERT(( is_same<int64_t,         upgrade<uint64_t, signed>::type> ));
  BOOST_MPL_ASSERT(( is_same<double,          upgrade<float>::type>            ));
  BOOST_MPL_ASSERT(( is_same<pack<double, 2>, upgrade< pack<float, 4> >::type> ));
}
