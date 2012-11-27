#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/meta/fusion.hpp>
#include <boost/dispatch/meta/as_signed.hpp>

using boost::array;
using boost::is_same;
using boost::dispatch::meta::as_signed;

int main()
{
  BOOST_MPL_ASSERT(( is_same<int          , as_signed<unsigned int>::type>   ));
  BOOST_MPL_ASSERT(( is_same<int          , as_signed<int>::type>            ));
  BOOST_MPL_ASSERT(( is_same<float        , as_signed<float>::type>          ));
  BOOST_MPL_ASSERT(( is_same<array<int,4> , as_signed<array<unsigned int,4> >::type>  ));
}
