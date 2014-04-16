//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/predicates/include/functions/is_nan.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>

using boost::simd::tag::is_nan_;

#define RS(T,V1,V2) (T, (V1) ,(V2))

namespace bench1 {
  typedef boost::simd::int16_t T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(is_nan_,(RS(vT,T(-10000),T(10000))))
}
namespace bench2 {
  typedef boost::simd::int32_t T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(is_nan_,(RS(vT,T(-10000),T(10000))))
}
namespace bench3 {
  typedef boost::simd::int64_t T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(is_nan_,(RS(vT,T(-10000),T(10000))))
}
namespace bench4 {
  typedef boost::simd::int8_t T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(is_nan_,(RS(vT,T(-128),T(127))))
}
namespace bench5 {
  typedef boost::simd::uint16_t T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(is_nan_,(RS(vT,T(0),T(10000))))
}
namespace bench6 {
  typedef boost::simd::uint32_t T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(is_nan_,(RS(vT,T(0),T(10000))))
}
namespace bench7 {
  typedef boost::simd::uint64_t T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(is_nan_,(RS(vT,T(0),T(10000))))
}
namespace bench8 {
  typedef boost::simd::uint8_t T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(is_nan_,(RS(vT,T(0),T(255))))
}
namespace bench9 {
  typedef double T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(is_nan_,(RS(vT,T(-10000),T(10000))))
}
namespace bench10 {
  typedef float T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(is_nan_,(RS(vT,T(-10000),T(10000))))
}
#undef RS
