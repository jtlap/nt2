//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_GSL_SPECFUN_FUNCTIONS_SCALAR_GSL_SF_DOUBLEFACT_HPP_INCLUDED
#define NT2_TOOLBOX_GSL_SPECFUN_FUNCTIONS_SCALAR_GSL_SF_DOUBLEFACT_HPP_INCLUDED
#include <nt2/toolbox/gsl_specfun/functions/gsl_sf_doublefact.hpp>
#include <nt2/toolbox/gsl_specfun/specific/interface.hpp>
  extern "C"{
    extern double gsl_sf_doublefact ( int );
  }
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is integer_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::gsl_specfun::tag::gsl_sf_doublefact_<T>, tag::cpu_,
		      (A0)(T),
		      (scalar_<integer_<A0> >)
		      )
  {
    typedef T result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return gsl_sf_doublefact(a0);
    }
  };
} }
#endif
