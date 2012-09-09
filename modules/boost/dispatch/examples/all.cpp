#include <boost/mpl/assert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/dispatch/meta/all.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace boost;
using namespace boost::mpl;

int main()
{
  BOOST_MPL_ASSERT    (( boost::dispatch::meta::all_seq<is_same<_,bool>, vector<bool,bool>  > ));
  BOOST_MPL_ASSERT    (( boost::dispatch::meta::all<is_same<_,bool>, bool,bool          > ));
  BOOST_MPL_ASSERT_NOT(( boost::dispatch::meta::all<is_same<_,bool>, vector<int,bool>   > ));
  BOOST_MPL_ASSERT_NOT(( boost::dispatch::meta::all<is_same<_,bool>, bool,float         > ));
}
