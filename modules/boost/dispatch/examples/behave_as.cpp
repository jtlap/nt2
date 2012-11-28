#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/as.hpp>
#include <boost/dispatch/meta/behave_as.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::mpl::_;
using boost::is_same;
using boost::dispatch::meta::as_;
using boost::dispatch::meta::behave_as;

int main()
{
  BOOST_MPL_ASSERT(( behave_as< is_same<_,float> , float    > ));
  BOOST_MPL_ASSERT(( behave_as< is_same<_,int>   , as_<int> > ));
}
