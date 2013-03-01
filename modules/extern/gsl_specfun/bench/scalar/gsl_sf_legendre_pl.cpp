//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_BENCH_MODULE "nt2 gsl_specfun toolbox - gsl_sf_legendre_pl/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of gsl_specfun components in scalar mode
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/gsl_specfun/include/functions/gsl_sf_legendre_pl.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <cmath>


//////////////////////////////////////////////////////////////////////////////
// scalar runtime benchmark for functor<gsl_sf_legendre_pl_> from gsl_specfun
//////////////////////////////////////////////////////////////////////////////
using nt2::gsl_specfun::tag::gsl_sf_legendre_pl_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) ,T(V2))

namespace n1 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  NT2_TIMING(gsl_sf_legendre_pl_,(RS(iT,iT(0),iT(10)))(RS(T,T(-1),T(1))))
}
namespace n2 {
  typedef double T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  NT2_TIMING(gsl_sf_legendre_pl_,(RS(iT,iT(0),iT(10)))(RS(T,T(-1),T(1))))
}

#undef RS
