#include <boost/simd/memory/is_power_of_2.hpp>
#include <boost/assert.hpp>

int main()
{
  BOOST_ASSERT(  boost::simd::is_power_of_2(   2 ) );
  BOOST_ASSERT(  boost::simd::is_power_of_2(  16 ) );
  BOOST_ASSERT( !boost::simd::is_power_of_2(   0 ) );
  BOOST_ASSERT( !boost::simd::is_power_of_2(1337 ) );
}
