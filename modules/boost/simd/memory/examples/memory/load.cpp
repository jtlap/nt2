#include <iostream>
#include <boost/simd/include/native.hpp>
#include <boost/simd/memory/stack_buffer.hpp>
#include <boost/simd/include/functions/load.hpp>

using boost::simd::load;
using boost::simd::native;

int main()
{
  typedef native<double,BOOST_SIMD_DEFAULT_EXTENSION> simd_t;
  BOOST_SIMD_ALIGNED_STACK_BUFFER( data, double, 15 );

  for(std::size_t i=0;i<15;++i) data[i] = double(1.f/(1+i));

  //============================================================================
  // Scalar loads
  //============================================================================
  // Regular scalar load
  std::cout << load<double>(&data[0]) << std::endl;

  // Scalar load with transtyping
  int d = load<int>(&data[0]);
  std::cout << d << std::endl;

  // Scalar load with offset
  std::cout << load<double>(&data[0],2) << std::endl;

  // Scalar load with "misalignment"
  std::cout << load<double,2>(&data[2]) << std::endl;

  // Scalar load with "misalignment" and offset
  std::cout << load<double,2>(&data[2],2) << std::endl;

  //============================================================================
  // SIMD loads
  //============================================================================
  // Regular SIMD load
  std::cout << load< simd_t >(&data[0]) << std::endl;

  // SIMD load with offset
  std::cout << load< simd_t >(&data[0], simd_t::size()) << std::endl;

  // SIMD load with "misalignment"
  std::cout << load<simd_t,2>(&data[2]) << std::endl;

  // SIMD load with "misalignment" and offset
  std::cout << load<simd_t,2>(&data[2],simd_t::size()) << std::endl;
}
