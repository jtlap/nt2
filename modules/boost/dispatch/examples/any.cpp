#include <boost/mpl/assert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/dispatch/meta/any.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace boost;
using namespace boost::mpl;

int main()
{
  BOOST_MPL_ASSERT    (( boost::dispatch::meta::any_seq<is_same<_,bool>, vector<float,bool>  > ));
  BOOST_MPL_ASSERT    (( boost::dispatch::meta::any<is_same<_,bool>, bool,float          > ));
  BOOST_MPL_ASSERT_NOT(( boost::dispatch::meta::any<is_same<_,bool>, vector<int,double>   > ));
  BOOST_MPL_ASSERT_NOT(( boost::dispatch::meta::any<is_same<_,bool>, double,float         > ));
}
