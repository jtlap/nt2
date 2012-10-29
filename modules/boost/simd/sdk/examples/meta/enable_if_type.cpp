#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;

template<class T, class Enable=void>
struct test
{
  typedef void type;
};

template<class T>
struct test<T,typename boost::dispatch::meta::enable_if_type<typename T::type>::type> : T
{};

struct foo { typedef float** type; };

int main()
{
  BOOST_MPL_ASSERT(( is_same<void     , test< float >::type>    ));
  BOOST_MPL_ASSERT(( is_same<float**  , test< foo >::type>      ));
}
