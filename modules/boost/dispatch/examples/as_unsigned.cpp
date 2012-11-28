#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/as_unsigned.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/meta/fusion.hpp>

using boost::array;
using boost::is_same;
using boost::dispatch::meta::as_unsigned;

int main()
{
  BOOST_MPL_ASSERT(( is_same<unsigned int           , as_unsigned<unsigned int>::type>  ));
  BOOST_MPL_ASSERT(( is_same<unsigned int           , as_unsigned<int>::type>           ));
  BOOST_MPL_ASSERT(( is_same<float                  , as_unsigned<float>::type>         ));
  BOOST_MPL_ASSERT(( is_same<array<unsigned int,4>  , as_unsigned<array<int,4> >::type> ));
}
