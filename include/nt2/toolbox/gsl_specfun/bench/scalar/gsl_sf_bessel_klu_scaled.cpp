//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/gsl_specfun/include/gsl_sf_bessel_klu_scaled.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <cmath>


//////////////////////////////////////////////////////////////////////////////
// scalar runtime benchmark for functor<gsl_sf_bessel_klu_scaled_> from gsl_specfun
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::gsl_sf_bessel_klu_scaled_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) ,T(V2))

namespace n1 {
  typedef float T;
  NT2_TIMING(nt2::tag::gsl_sf_bessel_klu_scaled_,(RS(iT,iT(-10),iT(10)))(RS(T,T(-10),T(10))))
}
namespace n2 {
  typedef double T;
  NT2_TIMING(nt2::tag::gsl_sf_bessel_klu_scaled_,(RS(iT,iT(-10),iT(10)))(RS(T,T(-10),T(10))))
}

#undef RS
