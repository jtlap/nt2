/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_COMPARE_LESS_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_COMPARE_LESS_HPP_INCLUDED

#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace functors
{
  template<class Info>
  struct call<simd::is_less_,tag::simd_(tag::arithmetic_,tag::sse_),Info>
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL_DISPATCH ( 2
                              , typename nt2::meta::scalar_of<A0>::type
                              , (3, (float,double,arithmetic_))
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(2,  float)
    {
      int mask_a_lt_b =  _mm_movemask_ps(lt(a0,a1));
      int mask_a_gt_b =  _mm_movemask_ps(gt(a0,a1));
      return compare(mask_a_lt_b,mask_a_gt_b);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2, double)
    {
      int mask_a_lt_b =  _mm_movemask_pd(lt(a0,a1));
      int mask_a_gt_b =  _mm_movemask_pd(gt(a0,a1));
      return compare(mask_a_lt_b,mask_a_gt_b);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      int mask_a_lt_b =  _mm_movemask_epi8(lt(a0,a1));
      int mask_a_gt_b =  _mm_movemask_epi8(gt(a0,a1));
      return compare(mask_a_lt_b,mask_a_gt_b);
    }

    private:
    bool compare(int mask_a_lt_b, int mask_a_gt_b) const
    {
      return    ( !mask_a_gt_b && mask_a_lt_b      )
            ||  (    !(mask_a_gt_b && !mask_a_lt_b )
                  &&  (mask_a_lt_b <   mask_a_gt_b )
                );
    }
  };
} }

#endif
