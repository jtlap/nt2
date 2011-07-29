#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/result_of.hpp>
#include <nt2/sdk/meta/arithmetic.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace boost;

int main()
{
  BOOST_MPL_ASSERT(( is_same<nt2::meta::result_of< nt2::meta::arithmetic(char) >::type, int>             ));
  BOOST_MPL_ASSERT(( is_same< nt2::meta::result_of< nt2::meta::arithmetic(int,float  ) >::type, float>   ));
  BOOST_MPL_ASSERT(( is_same< nt2::meta::result_of< nt2::meta::arithmetic(int,double ) >::type, double>  ));
}
