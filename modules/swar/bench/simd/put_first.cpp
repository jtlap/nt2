//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_BENCH_MODULE "nt2 swar toolbox - put_first/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of swar components in simd mode
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/swar/include/functions/put_first.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/unit/bench_includes.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <cmath>
typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;

//////////////////////////////////////////////////////////////////////////////
// simd runtime benchmark for functor<put_first_> from swar
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::put_first_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, (V1) ,(V2))

namespace n1 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(put_first_,(RS(vT,T(-100),T(100)))(RS(iT,0,nt2::meta::cardinal_of<T>::value-1)))
}
namespace n2 {
  typedef double T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(put_first_,(RS(vT,T(-100),T(100)))(RS(iT,0,nt2::meta::cardinal_of<T>::value-1)))
}
namespace n3 {
  typedef nt2::int8_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(put_first_,(RS(vT,nt2::Valmin<T>(),nt2::Valmax<T>()))(RS(iT,0,nt2::meta::cardinal_of<T>::value-1)))
}
namespace n4 {
  typedef nt2::int16_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(put_first_,(RS(vT,nt2::Valmin<T>(),nt2::Valmax<T>()))(RS(iT,0,nt2::meta::cardinal_of<T>::value-1)))
}
namespace n5 {
  typedef nt2::int32_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(put_first_,(RS(vT,nt2::Valmin<T>(),nt2::Valmax<T>()))(RS(iT,0,nt2::meta::cardinal_of<T>::value-1)))
}
namespace n6 {
  typedef nt2::int64_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(put_first_,(RS(vT,nt2::Valmin<T>(),nt2::Valmax<T>()))(RS(iT,0,nt2::meta::cardinal_of<T>::value-1)))
}
namespace n7 {
  typedef nt2::uint8_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(put_first_,(RS(vT,nt2::Valmin<T>(),nt2::Valmax<T>()))(RS(iT,0,nt2::meta::cardinal_of<T>::value-1)))
}
namespace n8 {
  typedef nt2::uint16_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(put_first_,(RS(vT,nt2::Valmin<T>(),nt2::Valmax<T>()))(RS(iT,0,nt2::meta::cardinal_of<T>::value-1)))
}
namespace n9 {
  typedef nt2::uint32_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(put_first_,(RS(vT,nt2::Valmin<T>(),nt2::Valmax<T>()))(RS(iT,0,nt2::meta::cardinal_of<T>::value-1)))
}
namespace n10 {
  typedef nt2::uint64_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::simd::native<iT,ext_t> viT;
  NT2_TIMING(put_first_,(RS(vT,nt2::Valmin<T>(),nt2::Valmax<T>()))(RS(iT,0,nt2::meta::cardinal_of<T>::value-1)))
}

#undef RS
