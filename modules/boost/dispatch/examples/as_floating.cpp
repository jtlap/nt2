#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/meta/as_floating.hpp>

using boost::is_same;

int main()
{
  BOOST_MPL_ASSERT(( is_same<float  , boost::dispatch::meta::as_floating<int>::type>  ));
  BOOST_MPL_ASSERT(( is_same<float  , boost::dispatch::meta::as_floating<unsigned int>::type> ));
  BOOST_MPL_ASSERT(( is_same<double , boost::dispatch::meta::as_floating<unsigned long >::type> ));
}
