#include <boost/mpl/assert.hpp>
#include <boost/mpl/vector.hpp>
#include <nt2/sdk/meta/all.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace boost;
using namespace boost::mpl;

int main()
{
  BOOST_MPL_ASSERT    (( nt2::meta::all_seq<is_same<_,bool>, vector<bool,bool> >  ));
  BOOST_MPL_ASSERT    (( nt2::meta::all<is_same<_,bool>, bool,bool >              ));
  BOOST_MPL_ASSERT_NOT(( nt2::meta::all<is_same<_,bool>, vector<int,bool> >       ));
  BOOST_MPL_ASSERT_NOT(( nt2::meta::all<is_same<_,bool>, bool,float >             ));
}
