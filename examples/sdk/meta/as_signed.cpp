#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;
using nt2::meta::as_signed;

struct test {};

int main()
{
  BOOST_MPL_ASSERT(( is_same<test, as_signed<test>::type>         ));
  BOOST_MPL_ASSERT(( is_same<int,  as_signed<unsigned int>::type> ));
  BOOST_MPL_ASSERT(( is_same<int,  as_signed<int>::type>          ));
}
