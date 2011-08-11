#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;

int main()
{
  BOOST_MPL_ASSERT(( is_same<int       , nt2::meta::as_signed<unsigned int>::type>         ));
  BOOST_MPL_ASSERT(( is_same<int       , nt2::meta::as_signed<int>::type>                  ));
  BOOST_MPL_ASSERT(( is_same<float     , nt2::meta::as_signed<float>::type>                ));
}
