#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/set.hpp>
#include <nt2/sdk/meta/is_set.hpp>

using nt2::meta::set;
using nt2::meta::is_set;

int main()
{
  BOOST_MPL_ASSERT    (( is_set< set<int,float,double**> >  ));
  BOOST_MPL_ASSERT_NOT(( is_set<float>                      ));
}

