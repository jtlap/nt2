//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_BENCH_MODULE "nt2 ieee toolbox - saturate_at/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of ieee components in scalar mode
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/ieee/include/functions/saturate_at.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <cmath>


//////////////////////////////////////////////////////////////////////////////
// scalar runtime benchmark for functor<saturate_at_> from ieee
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::saturate_at_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) ,T(V2))

namespace n1 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  NT2_TIMING(saturate_at_<nt2::tag::Pi>,(RS(T,-nt2::Ten<T>(),nt2::Ten<T>())))
}
namespace n2 {
  typedef double T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  NT2_TIMING(saturate_at_<nt2::tag::Pi>,(RS(T,-nt2::Ten<T>(),nt2::Ten<T>())))
}

#undef RS
