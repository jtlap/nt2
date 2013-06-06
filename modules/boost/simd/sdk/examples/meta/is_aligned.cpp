#include <boost/simd/meta/is_aligned.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/int.hpp>

int main()
{
  using boost::mpl::int_;

  BOOST_MPL_ASSERT    (( boost::simd::meta::is_aligned< int_<0>,int_<2> >::type   ));
  BOOST_MPL_ASSERT    (( boost::simd::meta::is_aligned< int_<4>,int_<2> >::type   ));
  BOOST_MPL_ASSERT_NOT(( boost::simd::meta::is_aligned< int_<17>,int_<2> >::type  ));
}
