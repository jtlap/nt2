#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/floating.hpp>
#include <nt2/sdk/meta/result_of.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace boost;

int main()
{
  BOOST_MPL_ASSERT(( is_same<nt2::meta::result_of< nt2::meta::floating(char) >::type, float>            ));
  BOOST_MPL_ASSERT(( is_same< nt2::meta::result_of< nt2::meta::floating(int,float  ) >::type, float>    ));
  BOOST_MPL_ASSERT(( is_same< nt2::meta::result_of< nt2::meta::floating(float,double ) >::type, double> ));
}
