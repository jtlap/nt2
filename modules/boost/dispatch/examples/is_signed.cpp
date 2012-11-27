#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/fusion.hpp>
#include <boost/dispatch/meta/is_signed.hpp>

using boost::array;
using boost::dispatch::meta::is_signed;

int main()
{
  BOOST_MPL_ASSERT_NOT(( is_signed<unsigned int>    ));
  BOOST_MPL_ASSERT    (( is_signed<int>             ));
  BOOST_MPL_ASSERT_NOT(( is_signed<bool>            ));
  BOOST_MPL_ASSERT    (( is_signed<float>           ));
  BOOST_MPL_ASSERT    (( is_signed< array<int,9> >  ));
}
