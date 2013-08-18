//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/dist.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

//////////////////////////////////////////////////////////////////////////////
// scalar runtime benchmark for functor<dist_> from boost.simd.arithmetic
//////////////////////////////////////////////////////////////////////////////
using boost::simd::tag::dist_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) ,T(V2))

namespace n1 {
  typedef float T;
  NT2_TIMING(dist_,(RS(T,-10.0f,10.0f))(RS(T,-10.0f,10.0f)))
}
namespace n2 {
  typedef double T;
  NT2_TIMING(dist_,(RS(T,-10.0,10.0))(RS(T,-10.0,10.0)))
}
namespace n3 {
  typedef boost::simd::int8_t T;
  NT2_TIMING(dist_,(RS(T,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(T,boost::simd::Valmin<T>(),boost::simd::Valmax<T>())))
}
namespace n4 {
  typedef boost::simd::int16_t T;
  NT2_TIMING(dist_,(RS(T,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(T,boost::simd::Valmin<T>(),boost::simd::Valmax<T>())))
}
namespace n5 {
  typedef boost::simd::int32_t T;
  NT2_TIMING(dist_,(RS(T,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(T,boost::simd::Valmin<T>(),boost::simd::Valmax<T>())))
}
namespace n6 {
  typedef boost::simd::int64_t T;
  NT2_TIMING(dist_,(RS(T,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(T,boost::simd::Valmin<T>(),boost::simd::Valmax<T>())))
}
namespace n7 {
  typedef boost::simd::uint8_t T;
  NT2_TIMING(dist_,(RS(T,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(T,boost::simd::Valmin<T>(),boost::simd::Valmax<T>())))
}
namespace n8 {
  typedef boost::simd::uint16_t T;
  NT2_TIMING(dist_,(RS(T,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(T,boost::simd::Valmin<T>(),boost::simd::Valmax<T>())))
}
namespace n9 {
  typedef boost::simd::uint32_t T;
  NT2_TIMING(dist_,(RS(T,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(T,boost::simd::Valmin<T>(),boost::simd::Valmax<T>())))
}
namespace n10 {
  typedef boost::simd::uint64_t T;
  NT2_TIMING(dist_,(RS(T,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(T,boost::simd::Valmin<T>(),boost::simd::Valmax<T>())))
}

#undef RS
