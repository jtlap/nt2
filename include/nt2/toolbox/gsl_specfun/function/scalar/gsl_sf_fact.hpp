//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_GSL_SPECFUN_FUNCTION_SCALAR_GSL_SF_FACT_HPP_INCLUDED
#define NT2_TOOLBOX_GSL_SPECFUN_FUNCTION_SCALAR_GSL_SF_FACT_HPP_INCLUDED

  extern "C"{
    extern double gsl_sf_fact ( int );
  }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(gsl_specfun::tag::gsl_sf_fact_, tag::cpu_,
		      (A0),
		      (integer_<A0>)
		      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<gsl_specfun::tag::gsl_sf_fact_(tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    typedef double result_type; 

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return ::gsl_sf_fact(a0);
    }
  };
} }

#endif
// modified by jt the 29/12/2010
