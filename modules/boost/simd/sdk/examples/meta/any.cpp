#include <boost/mpl/assert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/simd/sdk/meta/any.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace boost;
using namespace boost::mpl;

int main()
{
  BOOST_MPL_ASSERT    (( boost::simd::meta::any_seq<is_same<_,bool>, vector<float,bool> > ));
  BOOST_MPL_ASSERT    (( boost::simd::meta::any<is_same<_,bool>, int,bool >               ));
  BOOST_MPL_ASSERT_NOT(( boost::simd::meta::any<is_same<_,bool>, vector<int,char> >       ));
  BOOST_MPL_ASSERT_NOT(( boost::simd::meta::any<is_same<_,bool>, double,float >           ));
}
