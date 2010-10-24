//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_CEPHES_FUNCTION_SCALAR_LBETA_HPP_INCLUDED
#define NT2_TOOLBOX_CEPHES_FUNCTION_SCALAR_LBETA_HPP_INCLUDED

namespace nt2 { namespace functors
{
  extern "C"{
    extern double cephes_lbeta ( double,double );
    extern long double cephes_lbetal ( long double,long double );
  }
  /////////////////////////////////////////////////////////////////////////////
  // Compute lbeta(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<cephes::lbeta_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL_DISPATCH( 2, A0, (3, (double,long double,arithmetic_)) )
    NT2_FUNCTOR_CALL_EVAL_IF(2,  double){ return cephes_lbeta(a0, a1);}
    NT2_FUNCTOR_CALL_EVAL_IF(2,  long double){ return cephes_lbeta(a0, a1);}
    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type;
      return nt2::cephes::lbeta(type(a0), type(a1));
    }
  };
} }


      
#endif
