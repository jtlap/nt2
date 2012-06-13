#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/type_traits/is_same.hpp>

using nt2::int32_t;
using nt2::uint32_t;
using boost::is_same;

int main()
{
  BOOST_MPL_ASSERT(( is_same<int32_t,       nt2::meta::as_integer<float>::type>            ));
  BOOST_MPL_ASSERT(( is_same<uint32_t,      nt2::meta::as_integer<float, unsigned>::type>  ));
  BOOST_MPL_ASSERT(( is_same<int32_t,       nt2::meta::as_integer<uint32_t, signed>::type> ));
}
