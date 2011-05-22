#include <boost/mpl/assert.hpp>
#include <boost/tr1/functional.hpp>
#include <nt2/sdk/meta/arithmetic.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace boost;

int main()
{
  BOOST_MPL_ASSERT(( is_same<std::tr1::result_of< nt2::meta::arithmetic(char) >::type, int>             ));
  BOOST_MPL_ASSERT(( is_same< std::tr1::result_of< nt2::meta::arithmetic(int,float  ) >::type, float>   ));
  BOOST_MPL_ASSERT(( is_same< std::tr1::result_of< nt2::meta::arithmetic(int,double ) >::type, double>  ));
}
