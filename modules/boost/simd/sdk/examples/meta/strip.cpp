#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;

int main()
{
  BOOST_MPL_ASSERT(( is_same<float, nt2::meta::strip< float >::type >         ));
  BOOST_MPL_ASSERT(( is_same<float, nt2::meta::strip< volatile float >::type >));
  BOOST_MPL_ASSERT(( is_same<float, nt2::meta::strip< float& >::type >        ));
  BOOST_MPL_ASSERT(( is_same<float, nt2::meta::strip< float const >::type >   ));
  BOOST_MPL_ASSERT(( is_same<float, nt2::meta::strip< float const& >::type >  ));
}
