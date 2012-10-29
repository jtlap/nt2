#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;

int main()
{
  BOOST_MPL_ASSERT(( is_same<float, boost::dispatch::meta::strip< float >::type >         ));
  BOOST_MPL_ASSERT(( is_same<float, boost::dispatch::meta::strip< volatile float >::type >));
  BOOST_MPL_ASSERT(( is_same<float, boost::dispatch::meta::strip< float& >::type >        ));
  BOOST_MPL_ASSERT(( is_same<float, boost::dispatch::meta::strip< float const >::type >   ));
  BOOST_MPL_ASSERT(( is_same<float, boost::dispatch::meta::strip< float const& >::type >  ));
}
