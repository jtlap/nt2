#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/simd/pack.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;
using nt2::meta::as_signed;

using nt2::simd::pack;

int main()
{
  BOOST_MPL_ASSERT(( is_same<int,        as_signed<unsigned int>::type>         ));
  BOOST_MPL_ASSERT(( is_same<int,        as_signed<int>::type>                  ));
  BOOST_MPL_ASSERT(( is_same<float,      as_signed<float>::type>                ));
  BOOST_MPL_ASSERT(( is_same< pack<int>, as_signed< pack<unsigned int> >::type> ));
}
