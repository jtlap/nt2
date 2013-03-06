//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_GSL_SPECFUN_FUNCTIONS_GSL_SF_BESSEL_KNU_SCALED__HPP_INCLUDED
#define NT2_TOOLBOX_GSL_SPECFUN_FUNCTIONS_GSL_SF_BESSEL_KNU_SCALED__HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace gsl_specfun
{
  namespace tag
  {
    struct gsl_sf_bessel_knu_scaled__ : ext::elementwise_<gsl_sf_bessel_knu_scaled__> { typedef ext::elementwise_<gsl_sf_bessel_knu_scaled__> parent; };
  }

  NT2_FUNCTION_IMPLEMENTATION(gsl_specfun::tag::gsl_sf_bessel_knu_scaled__, gsl_sf_bessel_knu_scaled_, 2)
} }

#endif
