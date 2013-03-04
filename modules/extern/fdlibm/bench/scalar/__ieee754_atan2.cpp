//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_BENCH_MODULE "nt2 fdlibm toolbox - __ieee754_atan2/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of fdlibm components in scalar mode
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_atan2.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <cmath>


//////////////////////////////////////////////////////////////////////////////
// scalar runtime benchmark for functor<__ieee754_atan2_> from fdlibm
//////////////////////////////////////////////////////////////////////////////
using nt2::fdlibm::tag::__ieee754_atan2_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) ,T(V2))

namespace n1 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  NT2_TIMING(__ieee754_atan2_,(RS(T,T(-1),T(1)))(RS(T,T(-1),T(1))))
}
namespace n2 {
  typedef double T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  NT2_TIMING(__ieee754_atan2_,(RS(T,T(-1),T(1)))(RS(T,T(-1),T(1))))
}

#undef RS
