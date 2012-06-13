#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/meta/behave_as.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::mpl::_;
using boost::is_same;

int main()
{
  BOOST_MPL_ASSERT(( nt2::meta::behave_as< is_same<_,float> , float >               ));
  BOOST_MPL_ASSERT(( nt2::meta::behave_as< is_same<_,int>   , nt2::meta::as_<int> > ));
}
