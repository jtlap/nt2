#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/fusion.hpp>
#include <boost/dispatch/meta/is_fundamental.hpp>

using boost::array;
using boost::dispatch::meta::is_fundamental;

int main()
{
  BOOST_MPL_ASSERT    (( is_fundamental<bool>        ));
  BOOST_MPL_ASSERT    (( is_fundamental<int>         ));
  BOOST_MPL_ASSERT_NOT(( is_fundamental<int*>        ));
  BOOST_MPL_ASSERT_NOT(( is_fundamental< array<int,2> > ));
}
