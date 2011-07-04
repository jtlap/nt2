#include <boost/mpl/assert.hpp>
#include <nt2/sdk/simd/pack.hpp>
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;

int main()
{
  BOOST_MPL_ASSERT(( is_same<nt2::uint8_t             , nt2::meta::downgrade<uint16_t>::type>                     ));
  BOOST_MPL_ASSERT(( is_same<nt2::int8_t              , nt2::meta::downgrade<uint8_t, signed>::type>              ));
  BOOST_MPL_ASSERT(( is_same<float                    , nt2::meta::downgrade<double>::type>                        ));
  BOOST_MPL_ASSERT(( is_same<nt2::simd::pack<float, 4>, nt2::meta::downgrade< nt2::simd::pack<double, 2> >::type> ));
}
