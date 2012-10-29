#include <boost/cstdint.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/simd/sdk/aligned/next_power_of_2.hpp>

using boost::mpl::int_;
using boost::mpl::equal_to;
using boost::simd::meta::next_power_of_2;

int main()
{
  BOOST_MPL_ASSERT(( equal_to<next_power_of_2<int_<0> >::type,int_<0> >::type ));
  BOOST_MPL_ASSERT(( equal_to<next_power_of_2<int_<1> >::type,int_<1> >::type ));
  BOOST_MPL_ASSERT(( equal_to<next_power_of_2<int_<2> >::type,int_<2> >::type ));
  BOOST_MPL_ASSERT(( equal_to<next_power_of_2<int_<2> >::type,int_<2> >::type ));
  BOOST_MPL_ASSERT(( equal_to<next_power_of_2<int_<3> >::type,int_<4> >::type ));
  BOOST_MPL_ASSERT(( equal_to<next_power_of_2<int_<1055> >::type,int_<2048> >::type ));
}
