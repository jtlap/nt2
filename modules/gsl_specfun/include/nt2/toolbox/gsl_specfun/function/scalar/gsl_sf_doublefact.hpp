//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_GSL_SPECFUN_FUNCTION_SCALAR_GSL_SF_DOUBLEFACT_HPP_INCLUDED
#define NT2_TOOLBOX_GSL_SPECFUN_FUNCTION_SCALAR_GSL_SF_DOUBLEFACT_HPP_INCLUDED
#include <nt2/toolbox/gsl_specfun/specific/interface.hpp>

  extern "C"{
    extern double gsl_sf_doublefact ( int );
  }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is integer_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(gsl_specfun::tag::gsl_sf_doublefact_<T>, tag::cpu_,
		      (A0)(T),
		      (integer_<A0>)
		      )

namespace nt2 { namespace ext
{
  template<class T, class Dummy>
  struct call<gsl_specfun::tag::gsl_sf_doublefact_<T>(tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    typedef T result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return gsl_sf_doublefact(a0);
    }
  };
} }


#endif
// modified by jt the 29/12/2010
