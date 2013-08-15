//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
#include <boost/simd/arithmetic/include/functions/floor.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <cmath>


//////////////////////////////////////////////////////////////////////////////
// scalar runtime benchmark for functor<floor_> from boost.simd.arithmetic
//////////////////////////////////////////////////////////////////////////////
using boost::simd::tag::floor_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) ,T(V2))

namespace n1 {
  typedef float T;
  NT2_TIMING(floor_,(RS(T,T(-100),T(100))))
}
namespace n2 {
  typedef double T;
  NT2_TIMING(floor_,(RS(T,T(-100),T(100))))
}

namespace n3 {
  typedef boost::simd::int8_t T;
  NT2_TIMING(floor_,(RS(T,T(-100),T(100))))
}
namespace n4 {
  typedef boost::simd::int16_t T;
  NT2_TIMING(floor_,(RS(T,T(-100),T(100))))
}
namespace n5 {
  typedef boost::simd::int32_t T;
  NT2_TIMING(floor_,(RS(T,T(-100),T(100))))
}
namespace n6 {
  typedef boost::simd::int64_t T;
  NT2_TIMING(floor_,(RS(T,T(-100),T(100))))
}
namespace n7 {
  typedef boost::simd::uint8_t T;
  NT2_TIMING(floor_,(RS(T,T(0),T(100))))
}
namespace n8 {
  typedef boost::simd::uint16_t T;
  NT2_TIMING(floor_,(RS(T,T(0),T(100))))
}
namespace n9 {
  typedef boost::simd::uint32_t T;
  NT2_TIMING(floor_,(RS(T,T(0),T(100))))
}
namespace n10 {
  typedef boost::simd::uint64_t T;
  NT2_TIMING(floor_,(RS(T,T(0),T(100))))
}

#undef RS
