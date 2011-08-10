#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/as_unsigned.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;

int main()
{
  BOOST_MPL_ASSERT(( is_same<unsigned int       , nt2::meta::as_unsigned<unsigned int>::type> ));
  BOOST_MPL_ASSERT(( is_same<unsigned int       , nt2::meta::as_unsigned<int>::type>          ));
  BOOST_MPL_ASSERT(( is_same<float              , nt2::meta::as_unsigned<float>::type>        ));
}
