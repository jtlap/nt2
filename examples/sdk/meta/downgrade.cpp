#include <boost/mpl/assert.hpp>
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/simd/pack.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;
using boost::mpl::_;
using nt2::meta::downgrade;

using nt2::uint16_t;
using nt2::uint8_t;
using nt2::simd::pack;

int main()
{
  BOOST_MPL_ASSERT(( is_same<uint8_t,        downgrade<uint16_t>::type>          ));
  BOOST_MPL_ASSERT(( is_same<int8_t,         downgrade<uint8_t, signed>::type>   ));
  BOOST_MPL_ASSERT(( is_same<float,          downgrade<double>::type>            ));
  BOOST_MPL_ASSERT(( is_same<pack<float, 4>, downgrade< pack<double, 2> >::type> ));
}
