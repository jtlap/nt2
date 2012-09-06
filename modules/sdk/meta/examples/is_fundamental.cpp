#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/is_fundamental.hpp>

using nt2::meta::is_fundamental;

int main()
{
  BOOST_MPL_ASSERT    (( is_fundamental<bool>        ));
  BOOST_MPL_ASSERT    (( is_fundamental<int>         ));
  BOOST_MPL_ASSERT_NOT(( is_fundamental<int*>        ));
}
