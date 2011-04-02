//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_GSL_SPECFUN_FUNCTION_GSL_SF_DOUBLEFACT_HPP_INCLUDED
#define NT2_TOOLBOX_GSL_SPECFUN_FUNCTION_GSL_SF_DOUBLEFACT_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/gsl_specfun/include.hpp>
#include <nt2/toolbox/gsl_specfun/specific/interface.hpp>


namespace nt2 { namespace gsl_specfun { namespace tag
  {         
    template < class T> struct gsl_sf_doublefact_ {};
  }
  NT2_GSL_SPECFUN_FUNCTION_IMPLEMENTATION_TPL(gsl_sf_doublefact,1)
  //  NT2_FUNCTION_IMPLEMENTATION(gsl_specfun::tag::gsl_sf_doublefact_, gsl_sf_doublefact, 1)
  } }
 
#include <nt2/toolbox/gsl_specfun/function/scalar/gsl_sf_doublefact.hpp>
// #include NT2_GSL_SPECFUN_INCLUDE(gsl_sf_doublefact.hpp) 

 
#endif

// modified by jt the 29/12/2010
