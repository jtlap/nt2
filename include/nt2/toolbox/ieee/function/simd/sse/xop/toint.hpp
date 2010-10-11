//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_SSE_XOP_TOINT_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_SSE_XOP_TOINT_HPP_INCLUDED
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for toint

  template<class Extension,class Info>
  struct call<toint_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      { typedef typename meta::as_integer<A0>::type type; };

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (3, (float,double,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,  float)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
      type that =  {_mm256_cvttps_epi32(a0)};
      return  that; 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, double)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
      const type v = {{a0[0],a0[1], a0[2],a0[3]}}; //TODO with _mm_cvttpd_epi32 
      return v;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      return a0;
    }
  };
} }

#endif