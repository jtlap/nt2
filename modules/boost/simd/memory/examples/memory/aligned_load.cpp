#include <boost/simd/include/native.hpp>
#include <boost/simd/preprocessor/stack_buffer.hpp>
#include <boost/simd/include/functions/aligned_load.hpp>

using boost::simd::aligned_load;
using boost::simd::native;

int main()
{
  typedef native<double,BOOST_SIMD_DEFAULT_EXTENSION> simd_t;
  BOOST_SIMD_ALIGNED_STACK_BUFFER( data, double, 15 );

  // Regular scalar load
  double d = aligned_load<double>(&data[0]);

  // Scalar load with type casting
  int i = aligned_load<int>(&data[0]);

  // Scalar load with offset
  d = aligned_load<double>(&data[0],2);

  // Scalar load with "misalignment"
  d = aligned_load<double,2>(&data[0]+2);

  // Scalar load with "misalignment" and offset
  d = aligned_load<double,2>(&data[2],2);

  // Regular SIMD load
  simd_t vd = aligned_load<simd_t >(&data[0]);

  // SIMD load with offset
  vd = aligned_load<simd_t >(&data[0], simd_t::size());

  // SIMD load with "misalignment"
  vd =  aligned_load<simd_t,2>(&data[0]+2);

  // SIMD load with "misalignment" and offset
  vd = aligned_load<simd_t,2>(&data[2],simd_t::size());
}
