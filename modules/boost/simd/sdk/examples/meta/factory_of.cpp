#include <boost/mpl/apply.hpp>
#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/factory_of.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace boost;
using namespace boost::mpl;

int main()
{
  typedef nt2::meta::factory_of<float>::type                  factory_of_float;

  BOOST_MPL_ASSERT(( is_same<double, apply<factory_of_float,double>::type > ));
}
