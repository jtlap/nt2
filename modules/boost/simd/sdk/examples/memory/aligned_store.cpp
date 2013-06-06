#include <boost/simd/include/native.hpp>
#include <boost/simd/preprocessor/stack_buffer.hpp>
#include <boost/simd/include/functions/aligned_store.hpp>

using boost::simd::aligned_store;
using boost::simd::native;

int main()
{
  typedef native<double,BOOST_SIMD_DEFAULT_EXTENSION> simd_t;
  BOOST_SIMD_ALIGNED_STACK_BUFFER( data, double, 15 );

  // Regular scalar store
  aligned_store(4.3f,&data[0]);

  // Scalar store with type casting
  aligned_store(3,&data[0]);

  // Scalar store with offset
  aligned_store(2., &data[0],2);

  // Regular SIMD store
  simd_t vd;

  aligned_store(vd, &data[0]);

  // SIMD store with offset
  aligned_store(vd, &data[0], simd_t::size());
}
