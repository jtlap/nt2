#include <boost/simd/meta/prev_power_of_2.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/int.hpp>

int main()
{
  using boost::mpl::int_;

  typedef boost::simd::meta::prev_power_of_2_c<0    >::type  a0;
  typedef boost::simd::meta::prev_power_of_2_c<9    >::type  a9;
  typedef boost::simd::meta::prev_power_of_2_c<1055 >::type  a1055;

  BOOST_MPL_ASSERT(( boost::mpl::equal_to<a0    , int_<0>     >::type ));
  BOOST_MPL_ASSERT(( boost::mpl::equal_to<a9    , int_<8>     >::type ));
  BOOST_MPL_ASSERT(( boost::mpl::equal_to<a1055 , int_<1024>  >::type ));
}
