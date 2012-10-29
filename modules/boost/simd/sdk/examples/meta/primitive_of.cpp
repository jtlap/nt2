#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/as.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace boost;
using namespace boost::mpl;

int main()
{
  BOOST_MPL_ASSERT(( is_same<float, boost::dispatch::meta::primitive_of<float>::type >                  ));
  BOOST_MPL_ASSERT(( is_same<float, boost::dispatch::meta::primitive_of<boost::dispatch::meta::as_<float> >::type > ));
}
