//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_BENCH_MODULE "nt2 arithmetic toolbox - sqrt1pm1/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
#include <boost/simd/toolbox/arithmetic/include/functions/sqrt1pm1.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <cmath>
typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;

//////////////////////////////////////////////////////////////////////////////
// simd runtime benchmark for functor<sqrt1pm1_> from arithmetic
//////////////////////////////////////////////////////////////////////////////
using boost::simd::tag::sqrt1pm1_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, (V1) ,(V2))

namespace n1 {
  typedef float T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  BOOST_SIMD_TIMING(sqrt1pm1_,(RS(vT,T(-10),T(10))))
}
namespace n2 {
  typedef double T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  BOOST_SIMD_TIMING(sqrt1pm1_,(RS(vT,T(-10),T(10))))
}

#undef RS
