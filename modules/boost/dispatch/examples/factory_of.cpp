#include <boost/mpl/apply.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/factory_of.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;
using boost::mpl::apply;
using boost::dispatch::meta::factory_of;

int main()
{
  typedef factory_of<float>::type                  factory_of_float;

  BOOST_MPL_ASSERT(( is_same<double, apply<factory_of_float,double>::type > ));
}
