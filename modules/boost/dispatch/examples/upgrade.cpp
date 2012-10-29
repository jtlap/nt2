#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/fusion.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::array;
using boost::mpl::_;
using boost::is_same;
using boost::dispatch::meta::upgrade;

int main()
{
  BOOST_MPL_ASSERT(( is_same<unsigned short   , upgrade<unsigned char>::type>         ));
  BOOST_MPL_ASSERT(( is_same<signed short     , upgrade<unsigned char, signed>::type> ));
  BOOST_MPL_ASSERT(( is_same<double           , upgrade<float>::type>                 ));
  BOOST_MPL_ASSERT(( is_same<array<double, 2> , upgrade< array<float, 2> >::type>     ));
}
