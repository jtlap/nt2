//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_CEPHES_FUNCTION_SCALAR_KN_HPP_INCLUDED
#define NT2_TOOLBOX_CEPHES_FUNCTION_SCALAR_KN_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
        
namespace nt2 { namespace functors
{
  extern "C"{
    extern float cephes_knf ( int,float );
    extern double cephes_kn ( int,double );
    extern long double cephes_knl ( int,long double );
  }
  template<class Info>
  struct validate<cephes::kn_,tag::scalar_(tag::arithmetic_),Info>
    {
      template<class Sig> struct result;
      template<class This,class A0, class A1>
      struct result<This(A0, A1)> :
         meta::is_integral<A0>{};
    };
  /////////////////////////////////////////////////////////////////////////////
  // Compute kn(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<cephes::kn_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : boost::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL_DISPATCH( 2, A1, (4, (float,double,long double,arithmetic_)) )
    NT2_FUNCTOR_CALL_EVAL_IF(2,  float){ return cephes_kn(a0, a1);}
    NT2_FUNCTOR_CALL_EVAL_IF(2,  double){ return cephes_kn(a0, a1);}
    NT2_FUNCTOR_CALL_EVAL_IF(2,  long double){ return cephes_kn(a0, a1);}
    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type;
      return nt2::cephes::kn((a0), type(a1));
    }
  };
} }


      
#endif
