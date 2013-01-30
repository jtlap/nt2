//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_BENCH_MODULE "nt2 boost.simd.swar toolbox - cumsum/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of boost.simd.swar components in simd mode
//////////////////////////////////////////////////////////////////////////////
#include <boost/simd/toolbox/swar/include/functions/cumsum.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <cmath>
typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;

//////////////////////////////////////////////////////////////////////////////
// simd runtime benchmark for functor<cumsum_> from boost.simd.swar
//////////////////////////////////////////////////////////////////////////////
using boost::simd::tag::cumsum_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, (V1) ,(V2))

namespace n1 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cumsum_,(RS(vT,T(-100),T(100))))
}
namespace n2 {
  typedef double T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cumsum_,(RS(vT,T(-100),T(100))))
}
namespace n3 {
  typedef boost::simd::int8_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cumsum_,(RS(vT,boost::simd::Valmin<T>(),boost::simd::Valmax<T>())))
}
namespace n4 {
  typedef boost::simd::int16_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cumsum_,(RS(vT,boost::simd::Valmin<T>(),boost::simd::Valmax<T>())))
}
namespace n5 {
  typedef boost::simd::int32_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cumsum_,(RS(vT,boost::simd::Valmin<T>(),boost::simd::Valmax<T>())))
}
namespace n6 {
  typedef boost::simd::int64_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cumsum_,(RS(vT,boost::simd::Valmin<T>(),boost::simd::Valmax<T>())))
}
namespace n7 {
  typedef boost::simd::uint8_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cumsum_,(RS(vT,boost::simd::Valmin<T>(),boost::simd::Valmax<T>())))
}
namespace n8 {
  typedef boost::simd::uint16_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cumsum_,(RS(vT,boost::simd::Valmin<T>(),boost::simd::Valmax<T>())))
}
namespace n9 {
  typedef boost::simd::uint32_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cumsum_,(RS(vT,boost::simd::Valmin<T>(),boost::simd::Valmax<T>())))
}
namespace n10 {
  typedef boost::simd::uint64_t T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cumsum_,(RS(vT,boost::simd::Valmin<T>(),boost::simd::Valmax<T>())))
}

#undef RS
