//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_BENCH_MODULE "nt2 cephes toolbox - exp10/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of cephes components in scalar mode
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/cephes/include/functions/exp10.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <cmath>


//////////////////////////////////////////////////////////////////////////////
// scalar runtime benchmark for functor<exp10_> from cephes
//////////////////////////////////////////////////////////////////////////////
using nt2::cephes::tag::exp10_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) ,T(V2))

namespace n1 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  NT2_TIMING(exp10_,(RS(T,T(-30),T(30))))
}
namespace n2 {
  typedef double T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  NT2_TIMING(exp10_,(RS(T,T(-30),T(30))))
}

#undef RS
