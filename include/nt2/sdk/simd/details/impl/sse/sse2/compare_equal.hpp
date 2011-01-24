/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_COMPARE_EQUAL_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_COMPARE_EQUAL_HPP_INCLUDED

#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace functors
{
  template<class Info>
  struct call<tag::compare_equal_,tag::simd_(tag::arithmetic_,tag::sse_),Info>
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL_DISPATCH ( 2
                              , typename nt2::meta::scalar_of<A0>::type
                              , (3, (float,double,arithmetic_))
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(2,  float)
    {
      return _mm_movemask_ps(eq(a0,a1)) == 0X0F;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2, double)
    {
      return _mm_movemask_pd(eq(a0,a1)) == 0x03;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      return _mm_movemask_epi8(eq(a0,a1)) == 0xFFFF;
    }
  };
} }

#endif
