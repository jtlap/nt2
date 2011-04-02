//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_GSL_SPECFUN_FUNCTION_SCALAR_GSL_SF_LNCHOOSE_HPP_INCLUDED
#define NT2_TOOLBOX_GSL_SPECFUN_FUNCTION_SCALAR_GSL_SF_LNCHOOSE_HPP_INCLUDED

  extern "C"{
    double gsl_sf_lnchoose(int,  int);
  }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is int
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(gsl_specfun::tag::gsl_sf_lnchoose_, tag::cpu_,
                                 (A0)(A1),
                                 (integer_<A0>)(integer_<A1>)
                                )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<gsl_specfun::tag::gsl_sf_lnchoose_(tag::integer_,tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    typedef double result_type; 

    NT2_FUNCTOR_CALL(2){ return ::gsl_sf_lnchoose(a0, a1); }
  };
} }

#endif
// modified by jt the 29/12/2010
