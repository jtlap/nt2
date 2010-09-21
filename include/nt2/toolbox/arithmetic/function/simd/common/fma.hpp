//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_FMA_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_FMA_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for fma

  /////////////////////////////////////////////////////////////////////////////
  // Compute fma(const A0& a0, const A0& a1, const A0& a2)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<fma_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0,A0)>
      : meta::strip<A0>{};//
    NT2_FUNCTOR_CALL(3)
    {
      return a0*a1+a2; 
    }
  }; 
 //    NT2_FUNCTOR_CALL_DISPATCH(
//       3,
//       typename nt2::meta::scalar_of<A0>::type,
//       (3, (float,double,arithmetic_))
//     )
//     NT2_FUNCTOR_CALL_EVAL_IF(2,       float)
//     {
//       A0 that =  {_mm256_macc_ps(a0,a1,a2)}; return that;
//     }
//     NT2_FUNCTOR_CALL_EVAL_IF(2,      double)
//     {
//       A0 that =  {_mm256_macc_pd(a0,a1,a2)}; return that;
//     }
//     NT2_FUNCTOR_CALL_EVAL_IF(2,     int16_t)
//     {
//        NT2_XOP_JOIN128INT3(that, _mm_macc_epi16)}; return that;
//     }
} }

      
#endif
