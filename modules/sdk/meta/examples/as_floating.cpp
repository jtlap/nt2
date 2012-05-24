#include <boost/mpl/assert.hpp>
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <boost/type_traits/is_same.hpp>

using nt2::int32_t;
using nt2::uint32_t;
using nt2::uint64_t;
using boost::is_same;

int main()
{
  BOOST_MPL_ASSERT(( is_same<float,       nt2::meta::as_floating<int32_t>::type>         ));
  BOOST_MPL_ASSERT(( is_same<float,       nt2::meta::as_floating<uint32_t>::type>        ));
  BOOST_MPL_ASSERT(( is_same<double,      nt2::meta::as_floating<uint64_t>::type>        ));
}
