//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_GSL_SPECFUN_FUNCTION_GSL_SF_LEGENDRE_PL_HPP_INCLUDED
#define NT2_TOOLBOX_GSL_SPECFUN_FUNCTION_GSL_SF_LEGENDRE_PL_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/gsl_specfun/include.hpp>

namespace nt2 { namespace gsl_specfun { namespace tag
  {         
    struct gsl_sf_legendre_pl_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION(gsl_specfun::tag::gsl_sf_legendre_pl_, gsl_sf_legendre_pl, 2)
  } }
 
#include <nt2/toolbox/gsl_specfun/function/scalar/gsl_sf_legendre_pl.hpp>
// #include NT2_GSL_SPECFUN_INCLUDE(gsl_sf_legendre_Pl.hpp) 

 
#endif

// modified by jt the 29/12/2010