/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_MAKE_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_MAKE_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace functors
{
  template<class T, class Info>
  struct call<make_<T>,tag::simd_<tag::arithmetic_,tag::sse_>, Info>
  {
    typedef T result_type;

    NT2_FUNCTOR_CALL_DISPATCH ( 1, typename meta::scalar_of<T>::type
                              , (6, (double,float,int8_,int16_,int32_,int64_))
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(1,double)
    {
      T that = {{ a0[0],a0[1] }};
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,int64_)
    {
      T that = {{ a0[0],a0[1] }};
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,float)
    {
      T that = {{ a0[0],a0[1],a0[2],a0[3] }};
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,int32_)
    {
      T that = { _mm_setr_epi32(a0[0],a0[1],a0[2],a0[3]) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,int16_)
    {
      T that =  { _mm_setr_epi16( a0[0],a0[1],a0[2],a0[3]
                                , a0[4],a0[5],a0[6],a0[7]
                                )
                };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,int8_)
    {
      T that =  { _mm_setr_epi8 ( a0[0] ,a0[1] ,a0[2] ,a0[3]
                                , a0[4] ,a0[5] ,a0[6] ,a0[7]
                                , a0[8] ,a0[9] ,a0[10],a0[11]
                                , a0[12],a0[13],a0[14],a0[15]
                                )
                };
      return that;
    }
  };
} }

#endif
