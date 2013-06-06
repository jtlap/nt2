#include <boost/simd/meta/next_power_of_2.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/int.hpp>

int main()
{
  using boost::mpl::int_;

  typedef boost::simd::meta::next_power_of_2<int_<0>    >::type  a0;
  typedef boost::simd::meta::next_power_of_2<int_<3>    >::type  a3;
  typedef boost::simd::meta::next_power_of_2<int_<1055> >::type  a1055;

  BOOST_MPL_ASSERT(( boost::mpl::equal_to<a0    , int_<0>     >::type ));
  BOOST_MPL_ASSERT(( boost::mpl::equal_to<a3    , int_<4>     >::type ));
  BOOST_MPL_ASSERT(( boost::mpl::equal_to<a1055 , int_<2048>  >::type ));
}
