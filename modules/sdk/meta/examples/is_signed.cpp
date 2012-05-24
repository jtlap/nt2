#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/is_signed.hpp>

using nt2::meta::is_signed;

int main()
{
  BOOST_MPL_ASSERT_NOT(( is_signed<unsigned int> ));
  BOOST_MPL_ASSERT    (( is_signed<int>          ));
  BOOST_MPL_ASSERT_NOT(( is_signed<bool>         ));
  BOOST_MPL_ASSERT    (( is_signed<float>        ));
}
