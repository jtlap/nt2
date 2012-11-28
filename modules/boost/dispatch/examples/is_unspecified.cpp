#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/is_unspecified.hpp>

using boost::dispatch::meta::is_unspecified;

struct test {};

int main()
{
  BOOST_MPL_ASSERT_NOT(( is_unspecified<bool> ));
  BOOST_MPL_ASSERT_NOT(( is_unspecified<int>  ));
  BOOST_MPL_ASSERT    (( is_unspecified<int*> ));
  BOOST_MPL_ASSERT    (( is_unspecified<test> ));
}
