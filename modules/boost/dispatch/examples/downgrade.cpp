#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/fusion.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::array;
using boost::mpl::_;
using boost::is_same;
using boost::dispatch::meta::downgrade;

int main()
{
  BOOST_MPL_ASSERT(( is_same<unsigned char   , downgrade<unsigned short>::type>         ));
  BOOST_MPL_ASSERT(( is_same<signed char     , downgrade<unsigned short, signed>::type> ));
  BOOST_MPL_ASSERT(( is_same<float           , downgrade<double>::type>                 ));
  BOOST_MPL_ASSERT(( is_same<array<float, 2> , downgrade< array<double, 2> >::type>     ));
}
