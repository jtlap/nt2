#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/as_unsigned.hpp>
#include <nt2/sdk/simd/pack.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;
using nt2::meta::as_unsigned;

using nt2::simd::pack;

int main()
{
  BOOST_MPL_ASSERT(( is_same<unsigned int,        as_unsigned<unsigned int>::type> ));
  BOOST_MPL_ASSERT(( is_same<unsigned int,        as_unsigned<int>::type>          ));
  BOOST_MPL_ASSERT(( is_same<float,               as_unsigned<float>::type>        ));
  BOOST_MPL_ASSERT(( is_same< pack<unsigned int>, as_unsigned< pack<int> >::type>  ));
}
