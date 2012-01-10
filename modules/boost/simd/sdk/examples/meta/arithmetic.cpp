#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/result_of.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace boost;

int main()
{
  BOOST_MPL_ASSERT(( is_same<boost::common_type<char>::type, int>             ));
  BOOST_MPL_ASSERT(( is_same< boost::common_type<int,float  >::type, float>   ));
  BOOST_MPL_ASSERT(( is_same< boost::common_type<int,double >::type, double>  ));
}
