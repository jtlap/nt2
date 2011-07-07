//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_BENCH_MODULE "nt2 bitwise toolbox - rol/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////
#include <boost/simd/toolbox/bitwise/include/rol.hpp>
#include <boost/simd/sdk/unit/benchmark.hpp>
#include <boost/simd/sdk/unit/bench_includes.hpp>
#include <cmath>


//////////////////////////////////////////////////////////////////////////////
// scalar runtime benchmark for functor<rol_> from bitwise
//////////////////////////////////////////////////////////////////////////////
using boost::simd::tag::rol_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) ,T(V2))

namespace n1 {
  typedef boost::simd::int8_t T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  BOOST_SIMD_TIMING(rol_,(RS(T,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(iT,T(0),sizeof(T)*8-1)))
}
namespace n2 {
  typedef boost::simd::int16_t T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  BOOST_SIMD_TIMING(rol_,(RS(T,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(iT,T(0),sizeof(T)*8-1)))
}
namespace n3 {
  typedef boost::simd::int32_t T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  BOOST_SIMD_TIMING(rol_,(RS(T,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(iT,T(0),sizeof(T)*8-1)))
}
namespace n4 {
  typedef boost::simd::int64_t T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  BOOST_SIMD_TIMING(rol_,(RS(T,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(iT,T(0),sizeof(T)*8-1)))
}
namespace n5 {
  typedef boost::simd::uint8_t T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  BOOST_SIMD_TIMING(rol_,(RS(T,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(iT,T(0),sizeof(T)*8-1)))
}
namespace n6 {
  typedef boost::simd::uint16_t T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  BOOST_SIMD_TIMING(rol_,(RS(T,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(iT,T(0),sizeof(T)*8-1)))
}
namespace n7 {
  typedef boost::simd::uint32_t T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  BOOST_SIMD_TIMING(rol_,(RS(T,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(iT,T(0),sizeof(T)*8-1)))
}
namespace n8 {
  typedef boost::simd::uint64_t T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  BOOST_SIMD_TIMING(rol_,(RS(T,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(iT,T(0),sizeof(T)*8-1)))
}

#undef RS
