#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/simd/sdk/aligned/is_aligned.hpp>

using boost::mpl::int_;
using boost::simd::meta::is_aligned;

int main()
{
  BOOST_MPL_ASSERT(( is_aligned< int_<0>,int_<2> >::type ));
  BOOST_MPL_ASSERT(( is_aligned< int_<2>,int_<2> >::type ));
  BOOST_MPL_ASSERT(( is_aligned< int_<4>,int_<2> >::type ));
  BOOST_MPL_ASSERT(( is_aligned< int_<8>,int_<2> >::type ));
  BOOST_MPL_ASSERT_NOT(( is_aligned< int_<17>,int_<2> >::type ));
}
