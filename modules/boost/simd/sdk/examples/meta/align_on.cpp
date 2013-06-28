#include <boost/simd/meta/align_on.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/int.hpp>

int main()
{
  using boost::mpl::int_;

  typedef boost::simd::meta::align_on<int_<0>   ,int_<4> >::type  a0;
  typedef boost::simd::meta::align_on<int_<1>   ,int_<4> >::type  a1;
  typedef boost::simd::meta::align_on<int_<1055>,int_<4> >::type  a1055;

  BOOST_MPL_ASSERT(( boost::mpl::equal_to<a0    , int_<0>     >::type ));
  BOOST_MPL_ASSERT(( boost::mpl::equal_to<a1    , int_<4>     >::type ));
  BOOST_MPL_ASSERT(( boost::mpl::equal_to<a1055 , int_<1056>  >::type ));
}
