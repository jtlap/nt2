#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/is_scalar.hpp>

using boost::dispatch::meta::is_scalar;

int main()
{
  BOOST_MPL_ASSERT    (( is_scalar<int>       ));
  BOOST_MPL_ASSERT_NOT(( is_scalar<float*>    ));
}

