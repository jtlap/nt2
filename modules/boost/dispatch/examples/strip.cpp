#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;
using boost::dispatch::meta::strip;

int main()
{
  BOOST_MPL_ASSERT(( is_same<float, strip< float >::type >         ));
  BOOST_MPL_ASSERT(( is_same<float, strip< volatile float >::type >));
  BOOST_MPL_ASSERT(( is_same<float, strip< float& >::type >        ));
  BOOST_MPL_ASSERT(( is_same<float, strip< float const >::type >   ));
  BOOST_MPL_ASSERT(( is_same<float, strip< float const& >::type >  ));
}
