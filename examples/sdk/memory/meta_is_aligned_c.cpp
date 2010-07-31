#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <nt2/sdk/aligned/is_aligned.hpp>

using nt2::meta::is_aligned_c;

int main()
{
  BOOST_MPL_ASSERT(( is_aligned_c<0,2>::type ));
  BOOST_MPL_ASSERT(( is_aligned_c<2,2>::type ));
  BOOST_MPL_ASSERT(( is_aligned_c<4,2>::type ));
  BOOST_MPL_ASSERT(( is_aligned_c<8,2>::type ));
  BOOST_MPL_ASSERT_NOT(( is_aligned_c<17,2>::type ));
}
