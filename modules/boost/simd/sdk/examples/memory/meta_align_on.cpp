#include <boost/mpl/int.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/simd/sdk/memory/align_on.hpp>

using boost::mpl::int_;
using boost::mpl::equal_to;
using boost::simd::meta::align_on;

int main()
{
  BOOST_MPL_ASSERT(( equal_to<align_on<int_<0>,int_<4> >::type,int_<0> >::type ));
  BOOST_MPL_ASSERT(( equal_to<align_on<int_<1>,int_<4> >::type,int_<4> >::type ));
  BOOST_MPL_ASSERT(( equal_to<align_on<int_<1055>,int_<4> >::type,int_<1056> >::type ));
}
