#include <boost/mpl/assert.hpp>
#include <boost/simd/sdk/config/types.hpp>
#include <boost/dispatch/meta/make_integer.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::is_same;
using boost::mpl::_;
using boost::dispatch::meta::make_integer;

using boost::simd::uint32_t;
using boost::simd::uint64_t;

template<typename T>
struct test {};

int main()
{
  BOOST_MPL_ASSERT(( is_same<uint32_t,       make_integer<4>::type>                     ));
  BOOST_MPL_ASSERT(( is_same<int64_t,        make_integer<8, signed>::type>             ));
  BOOST_MPL_ASSERT(( is_same<test<uint64_t>, make_integer<8, unsigned, test<_> >::type> ));
}
