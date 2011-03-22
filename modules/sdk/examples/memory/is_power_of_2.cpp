#include <boost/cstdint.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <nt2/sdk/aligned/is_power_of_2.hpp>

using nt2::meta::is_power_of_2;

int main()
{
  BOOST_MPL_ASSERT(( is_power_of_2< boost::mpl::int_<2> >::type ));
  BOOST_MPL_ASSERT(( is_power_of_2< boost::mpl::int_<4> >::type ));
  BOOST_MPL_ASSERT(( is_power_of_2< boost::mpl::int_<8> >::type ));
  BOOST_MPL_ASSERT_NOT(( is_power_of_2< boost::mpl::int_<0> >::type ));
  BOOST_MPL_ASSERT_NOT(( is_power_of_2< boost::mpl::int_<10> >::type ));
}
