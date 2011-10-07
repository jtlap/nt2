#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/make_floating.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;
using boost::mpl::_;
using nt2::meta::make_floating;

template<typename T>
struct test {};

int main()
{
  BOOST_MPL_ASSERT(( is_same<float,       make_floating<4>::type>           ));
  BOOST_MPL_ASSERT(( is_same<double,      make_floating<8>::type>           ));
  BOOST_MPL_ASSERT(( is_same<test<float>, make_floating<4, test<_> >::type> ));
}
