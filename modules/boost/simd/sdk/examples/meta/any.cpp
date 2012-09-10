#include <boost/mpl/assert.hpp>
#include <boost/mpl/vector.hpp>
#include <nt2/sdk/meta/any.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace boost;
using namespace boost::mpl;

int main()
{
  BOOST_MPL_ASSERT    (( nt2::meta::any_seq<is_same<_,bool>, vector<float,bool> > ));
  BOOST_MPL_ASSERT    (( nt2::meta::any<is_same<_,bool>, int,bool >               ));
  BOOST_MPL_ASSERT_NOT(( nt2::meta::any<is_same<_,bool>, vector<int,char> >       ));
  BOOST_MPL_ASSERT_NOT(( nt2::meta::any<is_same<_,bool>, double,float >           ));
}
