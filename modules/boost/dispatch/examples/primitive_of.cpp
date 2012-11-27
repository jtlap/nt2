#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/as.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;
using boost::dispatch::meta::as_;
using boost::dispatch::meta::primitive_of;

int main()
{
  BOOST_MPL_ASSERT(( is_same<float, primitive_of<float>::type >       ));
  BOOST_MPL_ASSERT(( is_same<float, primitive_of<as_<float> >::type > ));
}
