//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_SSE_SSSE3_NEGATION_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_SSE_SSSE3_NEGATION_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for negation

  template<class Extension,class Info>
  struct call<negation_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (5, (real_,int32_t,int16_t,int8_t,uint32_t))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,    real_)
    {
       /*PUT CODE HERE*/
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,  int32_t)
    {
       /*PUT CODE HERE*/
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,  int16_t)
    {
       /*PUT CODE HERE*/
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,   int8_t)
    {
       /*PUT CODE HERE*/
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, uint32_t)
    {
       /*PUT CODE HERE*/
    }
  };
} }

#endif