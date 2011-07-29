#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/sign_of.hpp>
#include <nt2/sdk/simd/pack.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;
using nt2::meta::sign_of;

using nt2::simd::pack;

int main()
{
  BOOST_MPL_ASSERT(( is_same<unsigned, sign_of<unsigned int>::type> ));
  BOOST_MPL_ASSERT(( is_same<signed,   sign_of<int>::type>          ));
  BOOST_MPL_ASSERT(( is_same<unsigned, sign_of<bool>::type>         ));
  BOOST_MPL_ASSERT(( is_same<signed,   sign_of<float>::type>        ));
  BOOST_MPL_ASSERT(( is_same<signed,   sign_of< pack<int> >::type>  ));
}
