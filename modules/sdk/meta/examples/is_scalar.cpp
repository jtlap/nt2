#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/is_scalar.hpp>

using nt2::meta::is_scalar;

int main()
{
  BOOST_MPL_ASSERT    (( is_scalar<int>       ));
  BOOST_MPL_ASSERT_NOT(( is_scalar<float*>    ));
}

