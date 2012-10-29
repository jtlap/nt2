#include <boost/mpl/assert.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/config/types.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;

int main()
{
  BOOST_MPL_ASSERT(( is_same<boost::simd::uint8_t             , boost::dispatch::meta::downgrade<uint16_t>::type>                     ));
  BOOST_MPL_ASSERT(( is_same<boost::simd::int8_t              , boost::dispatch::meta::downgrade<uint8_t, signed>::type>              ));
  BOOST_MPL_ASSERT(( is_same<float                    , boost::dispatch::meta::downgrade<double>::type>                        ));
  BOOST_MPL_ASSERT(( is_same<boost::simd::pack<float, 4>, boost::dispatch::meta::downgrade< boost::simd::pack<double, 2> >::type> ));
}
