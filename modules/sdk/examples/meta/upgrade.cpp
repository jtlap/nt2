#include <boost/mpl/assert.hpp>
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/simd/pack.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;
using boost::mpl::_;
using nt2::meta::upgrade;

using nt2::uint32_t;
using nt2::uint64_t;
using nt2::simd::pack;

int main()
{
  BOOST_MPL_ASSERT(( is_same<uint32_t,        upgrade<uint16_t>::type>         ));
  BOOST_MPL_ASSERT(( is_same<int64_t,         upgrade<uint64_t, signed>::type> ));
  BOOST_MPL_ASSERT(( is_same<double,          upgrade<float>::type>            ));
  BOOST_MPL_ASSERT(( is_same<pack<double, 2>, upgrade< pack<float, 4> >::type> ));
}
