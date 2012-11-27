#include <boost/mpl/assert.hpp>
#include <nt2/sdk/config/types.hpp>
#include <boost/dispatch/meta/make_integer.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::mpl::_;
using boost::is_same;
using boost::dispatch::meta::make_integer;

template<typename T> struct test {};

int main()
{
  BOOST_MPL_ASSERT(( is_same<unsigned char      , make_integer<1>::type>                    ));
  BOOST_MPL_ASSERT(( is_same<signed char        , make_integer<1, signed>::type>            ));
  BOOST_MPL_ASSERT(( is_same<test<signed short> , make_integer<2, signed, test<_> >::type>  ));
}
