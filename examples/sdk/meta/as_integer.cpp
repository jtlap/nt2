#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/simd/pack.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;
using nt2::meta::as_integer;

using nt2::uint32_t;
using nt2::int32_t;
using nt2::simd::pack;

int main()
{
  BOOST_MPL_ASSERT(( is_same<int32_t,       as_integer<float>::type>            ));
  BOOST_MPL_ASSERT(( is_same<uint32_t,      as_integer<float, unsigned>::type>  ));
  BOOST_MPL_ASSERT(( is_same<int32_t,       as_integer<uint32_t, signed>::type> ));
  BOOST_MPL_ASSERT(( is_same<pack<int32_t>, as_integer< pack<float> >::type>    ));
}
