#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/make_real.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;
using boost::mpl::_;
using nt2::meta::make_real;

template<typename T>
struct test {};

int main()
{
  BOOST_MPL_ASSERT(( is_same<float,       make_real<4>::type>           ));
  BOOST_MPL_ASSERT(( is_same<double,      make_real<8>::type>           ));
  BOOST_MPL_ASSERT(( is_same<test<float>, make_real<4, test<_> >::type> ));
}
