#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/as_unsigned.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;
using nt2::meta::as_unsigned;

struct test {};

int main()
{
  BOOST_MPL_ASSERT(( is_same<test,         as_unsigned<test>::type>         ));
  BOOST_MPL_ASSERT(( is_same<unsigned int, as_unsigned<unsigned int>::type> ));
  BOOST_MPL_ASSERT(( is_same<unsigned int, as_unsigned<int>::type>          ));
}
