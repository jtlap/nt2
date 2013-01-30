//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_BENCH_MODULE "nt2 boost.simd.predicates toolbox - is_not_greater/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of boost.simd.predicates components in simd mode
//////////////////////////////////////////////////////////////////////////////
#include <boost/simd/toolbox/predicates/include/functions/is_not_greater.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <cmath>
typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;

//////////////////////////////////////////////////////////////////////////////
// simd runtime benchmark for functor<is_not_greater_> from boost.simd.predicates
//////////////////////////////////////////////////////////////////////////////
using boost::simd::tag::is_not_greater_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, (V1) ,(V2))

namespace n1 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(is_not_greater_,(RS(vT,T(-10000),T(10000)))(RS(vT,T(-10000),T(10000))))
}
namespace n2 {
  typedef double T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(is_not_greater_,(RS(vT,T(-10000),T(10000)))(RS(vT,T(-10000),T(10000))))
}

#undef RS
