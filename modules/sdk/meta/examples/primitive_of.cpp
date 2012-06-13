#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/meta/primitive_of.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace boost;
using namespace boost::mpl;

int main()
{
  BOOST_MPL_ASSERT(( is_same<float, nt2::meta::primitive_of<float>::type >                  ));
  BOOST_MPL_ASSERT(( is_same<float, nt2::meta::primitive_of<nt2::meta::as_<float> >::type > ));
}
