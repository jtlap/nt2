#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

using boost::is_same;

int main()
{
  BOOST_MPL_ASSERT(( is_same<int, boost::dispatch::meta::as_integer<float>::type> ));
  BOOST_MPL_ASSERT(( is_same<unsigned int , boost::dispatch::meta::as_integer<float, unsigned>::type> ));
  BOOST_MPL_ASSERT(( is_same<int, boost::dispatch::meta::as_integer<uint32_t, signed>::type> ));
}
