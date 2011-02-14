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

////////////////////////////////////////////////////////////////////////////////
// Overload registration
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::compare_equal_, tag::cpu_, (A0)
                      , ((simd_<double_<A0>,tag::sse_>))
                        ((simd_<double_<A0>,tag::sse_>))
                      );

NT2_REGISTER_DISPATCH ( tag::compare_equal_, tag::cpu_, (A0)
                      , ((simd_<float_<A0>,tag::sse_>))
                        ((simd_<float_<A0>,tag::sse_>))
                      );

NT2_REGISTER_DISPATCH ( tag::compare_equal_, tag::cpu_, (A0)
                      , ((simd_<integer_<A0>,tag::sse_>))
                        ((simd_<integer_<A0>,tag::sse_>))
                      );

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::compare_equal_ ( tag::simd_<tag::double_,tag::sse_>
                                    , tag::simd_<tag::double_,tag::sse_>
                                    )
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef bool result_type;
    NT2_FUNCTOR_CALL(2) { return _mm_movemask_pd(eq(a0,a1)) == 0X03; }
  };

  template<class Dummy>
  struct  call< tag::compare_equal_ ( tag::simd_<tag::float_,tag::sse_>
                                    , tag::simd_<tag::float_,tag::sse_>
                                    )
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef bool result_type;
    NT2_FUNCTOR_CALL(2) { return _mm_movemask_ps(eq(a0,a1)) == 0X0F; }
  };

  template<class Dummy>
  struct  call< tag::compare_equal_ ( tag::simd_<tag::integer_,tag::sse_>
                                    , tag::simd_<tag::integer_,tag::sse_>
                                    )
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef bool result_type;
    NT2_FUNCTOR_CALL(2) { return _mm_movemask_epi8(eq(a0,a1)) == 0XFFFF; }
  };
} }

#endif
