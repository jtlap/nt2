//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_GSL_SPECFUN_FUNCTION_SIMD_COMMON_GSL_SF_BESSEL_JN_HPP_INCLUDED
#define NT2_TOOLBOX_GSL_SPECFUN_FUNCTION_SIMD_COMMON_GSL_SF_BESSEL_JN_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>

namespace nt2 { namespace functors
{
  /////////////////////////////////////////////////////////////////////////////
  // Compute gsl_sf_bessel_Jn(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Dummy>
  struct call<gsl_specfun::gsl_sf_bessel_Jn_,
              tag::simd_<tag::arithmetic_,Extension),Dummy>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)> : meta::strip<A0>{};

    // see documentation http://nt2.lri.fr/extension/custom_function.html
    // for writing the functor implementation code 
    // with or without type dispatching

  };
} }

      
#endif
