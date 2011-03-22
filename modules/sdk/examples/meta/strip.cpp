#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;
using nt2::meta::strip;

int main()
{
  BOOST_MPL_ASSERT(( is_same<float, strip< float >::type>        ));
  BOOST_MPL_ASSERT(( is_same<float, strip< float& >::type>       ));
  BOOST_MPL_ASSERT(( is_same<float, strip< float const >::type>  ));
  BOOST_MPL_ASSERT(( is_same<float, strip< float const& >::type> ));
}
