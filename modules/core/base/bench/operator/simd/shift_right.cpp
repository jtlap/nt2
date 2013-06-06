//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_BENCH_MODULE "nt2 operator toolbox - shift_right/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of operator components in simd mode
//////////////////////////////////////////////////////////////////////////////
#include <nt2/operator/include/functions/shift_right.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <cmath>
typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;

//////////////////////////////////////////////////////////////////////////////
// simd runtime benchmark for functor<shift_right_> from operator
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::shift_right_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, (V1) ,(V2))

namespace n1 {
  typedef nt2::int8_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(shift_right_,(RS(vT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2))(RS(viT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2)))
}
namespace n2 {
  typedef nt2::int16_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(shift_right_,(RS(vT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2))(RS(viT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2)))
}
namespace n3 {
  typedef nt2::int32_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(shift_right_,(RS(vT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2))(RS(viT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2)))
}
namespace n4 {
  typedef nt2::int64_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(shift_right_,(RS(vT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2))(RS(viT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2)))
}
namespace n5 {
  typedef nt2::uint8_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(shift_right_,(RS(vT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2))(RS(viT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2)))
}
namespace n6 {
  typedef nt2::uint16_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(shift_right_,(RS(vT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2))(RS(viT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2)))
}
namespace n7 {
  typedef nt2::uint32_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(shift_right_,(RS(vT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2))(RS(viT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2)))
}
namespace n8 {
  typedef nt2::uint64_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(shift_right_,(RS(vT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2))(RS(viT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2)))
}
namespace n9 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(shift_right_,(RS(vT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2))(RS(viT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2)))
}
namespace n10 {
  typedef double T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(shift_right_,(RS(vT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2))(RS(viT,nt2::Valmin<T>()/2,nt2::Valmax<T>()/2)))
}
namespace n11 {
  typedef boost::simd::uint8_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(shit_right_,(RS(vT,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(iT,T(0),sizeof(T)*8-1)))
}
namespace n12 {
  typedef boost::simd::uint16_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(shit_right_,(RS(vT,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(iT,T(0),sizeof(T)*8-1)))
}
namespace n13 {
  typedef boost::simd::uint32_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(shit_right_,(RS(vT,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(iT,T(0),sizeof(T)*8-1)))
}
namespace n14 {
  typedef boost::simd::uint64_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(shit_right_,(RS(vT,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(iT,T(0),sizeof(T)*8-1)))
}
namespace n15 {
  typedef boost::simd::int8_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(shit_right_,(RS(vT,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(iT,T(0),sizeof(T)*8-1)))
}
namespace n16 {
  typedef boost::simd::int16_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(shit_right_,(RS(vT,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(iT,T(0),sizeof(T)*8-1)))
}
namespace n17 {
  typedef boost::simd::int32_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(shit_right_,(RS(vT,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(iT,T(0),sizeof(T)*8-1)))
}
namespace n18 {
  typedef boost::simd::int64_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(shit_right_,(RS(vT,boost::simd::Valmin<T>()/2,boost::simd::Valmax<T>()/2))(RS(iT,T(0),sizeof(T)*8-1)))
}

#undef RS
