#include <boost/simd/meta/is_aligned.hpp>
#include <boost/mpl/assert.hpp>

int main()
{
  BOOST_MPL_ASSERT    (( boost::simd::meta::is_aligned_c<0  , 2>::type  ));
  BOOST_MPL_ASSERT    (( boost::simd::meta::is_aligned_c<4  , 2>::type  ));
  BOOST_MPL_ASSERT_NOT(( boost::simd::meta::is_aligned_c<17 , 2>::type  ));
}
