//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_BENCH_MODULE "nt2 euler toolbox - erfinv/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of euler components in simd mode
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/euler/include/functions/erfinv.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/unit/bench_includes.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <cmath>
typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;

//////////////////////////////////////////////////////////////////////////////
// simd runtime benchmark for functor<erfinv_> from euler
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::erfinv_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, (V1) ,(V2))

namespace n1 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(erfinv_,(RS(vT,T(-1),T(1))))
}
namespace n2 {
  typedef double T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(erfinv_,(RS(vT,T(-1),T(1))))
}
namespace n3 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(erfinv_,(RS(vT,T(-0.7),T(0.7))))
}
namespace n4 {
  typedef double T;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  NT2_TIMING(erfinv_,(RS(vT,T(-0.7),T(0.7))))
}
namespace n5 {
  typedef float T;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  NT2_TIMING(erfinv_,(RS(vT,T(0.7),T(1))))
}
namespace n6 {
  typedef double T;
  typedef boost::simd::native<T,ext_t> vT;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  NT2_TIMING(erfinv_,(RS(vT,T(0.7),T(1))))
}
#undef RS
