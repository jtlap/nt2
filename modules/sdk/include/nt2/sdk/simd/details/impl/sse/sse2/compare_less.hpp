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

////////////////////////////////////////////////////////////////////////////////
// Overload registration
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::compare_less_, tag::cpu_, (A0)
                      , ((simd_<double_<A0>,tag::sse_>))
                        ((simd_<double_<A0>,tag::sse_>))
                      );

NT2_REGISTER_DISPATCH ( tag::compare_less_, tag::cpu_, (A0)
                      , ((simd_<float_<A0>,tag::sse_>))
                        ((simd_<float_<A0>,tag::sse_>))
                      );

NT2_REGISTER_DISPATCH ( tag::compare_less_, tag::cpu_, (A0)
                      , ((simd_<integer_<A0>,tag::sse_>))
                        ((simd_<integer_<A0>,tag::sse_>))
                      );

////////////////////////////////////////////////////////////////////////////////
// Local shared helper
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace details
{
  inline bool compare_less_helper(int mask_a_lt_b, int mask_a_gt_b)
  {
  return    ( !mask_a_gt_b && mask_a_lt_b      )
        ||  (    !(mask_a_gt_b && !mask_a_lt_b )
              &&  (mask_a_lt_b <   mask_a_gt_b )
            );
  }
} }
////////////////////////////////////////////////////////////////////////////////
// Overloads implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::compare_less_( tag::simd_<tag::double_,tag::sse_>
                                  , tag::simd_<tag::double_,tag::sse_>
                                  )
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef bool result_type;
    NT2_FUNCTOR_CALL(2)
    {
      int mask_a_lt_b =  _mm_movemask_pd(lt(a0,a1));
      int mask_a_gt_b =  _mm_movemask_pd(gt(a0,a1));
      return compare_less_helper(mask_a_lt_b,mask_a_gt_b);
    }
  };

  template<class Dummy>
  struct  call< tag::compare_less_( tag::simd_<tag::float_,tag::sse_>
                                  , tag::simd_<tag::float_,tag::sse_>
                                  )
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef bool result_type;
    NT2_FUNCTOR_CALL(2)
    {
      int mask_a_lt_b =  _mm_movemask_ps(lt(a0,a1));
      int mask_a_gt_b =  _mm_movemask_ps(gt(a0,a1));
      return compare_less_helper(mask_a_lt_b,mask_a_gt_b);
    }
  };

  template<class Dummy>
  struct  call< tag::compare_less_( tag::simd_<tag::integer_,tag::sse_>
                                  , tag::simd_<tag::integer_,tag::sse_>
                                  )
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef bool result_type;
    NT2_FUNCTOR_CALL(2)
    {
      int mask_a_lt_b =  _mm_movemask_epi8(lt(a0,a1));
      int mask_a_gt_b =  _mm_movemask_epi8(gt(a0,a1));
      return compare_less_helper(mask_a_lt_b,mask_a_gt_b);
    }
  };
} }

#endif
