#include <boost/mpl/assert.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/dispatch/meta/as.hpp>
#include <boost/dispatch/meta/behave_as.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::mpl::_;
using boost::is_same;

int main()
{
  BOOST_MPL_ASSERT(( boost::dispatch::meta::behave_as< is_same<_,float> , float >               ));
  BOOST_MPL_ASSERT(( boost::dispatch::meta::behave_as< is_same<_,int>   , boost::dispatch::meta::as_<int> > ));
}
