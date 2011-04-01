/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_DIVIDES_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_DIVIDES_HPP_INCLUDED


////////////////////////////////////////////////////////////////////////////////
// Overload registration
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::divides_, tag::cpu_, (A0)
                      , ((simd_<double_<A0>,tag::sse_>))
                        ((simd_<double_<A0>,tag::sse_>))
                      );

NT2_REGISTER_DISPATCH ( tag::divides_, tag::cpu_, (A0)
                      , ((simd_<float_<A0>,tag::sse_>))
                        ((simd_<float_<A0>,tag::sse_>))
                      );

NT2_REGISTER_DISPATCH ( tag::divides_, tag::cpu_, (A0)
                      , ((simd_<integer_<A0>,tag::sse_>))
                        ((simd_<integer_<A0>,tag::sse_>))
                      );


////////////////////////////////////////////////////////////////////////////////
// Overloads implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  //////////////////////////////////////////////////////////////////////////////
  // dobule and float has an intrinsic
  //////////////////////////////////////////////////////////////////////////////
  template<class Dummy>
  struct  call< tag::divides_ ( tag::simd_<tag::double_,tag::sse_>
                              , tag::simd_<tag::double_,tag::sse_>
                              )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0  that = { _mm_div_pd(a0,a1) };
      return b_or(b_and(eq(a0, Zero<A0>()), eq(a1, Zero<A0>())),that);
    }
  };

  template<class Dummy>
  struct  call< tag::divides_ ( tag::simd_<tag::float_,tag::sse_>
                              , tag::simd_<tag::float_,tag::sse_>
                              )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0  that = { _mm_div_ps(a0,a1) };
      return  b_or(b_and(eq(a0, Zero<A0>()), eq(a1, Zero<A0>())),that);
    }
  };

  template<class Dummy>
  struct  call< tag::divides_ ( tag::simd_<tag::integer_,tag::sse_>
                              , tag::simd_<tag::integer_,tag::sse_>
                              )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      const A0 iseqza1 = eq(a1, Zero<A0>());
      const A0 aa0 = (a0-b_and(iseqza1, a0));
      const A0 aa1 = (a1+b_and(iseqza1, One<A0>())); 
      return map(functor<tag::divides_>(),aa0,aa1);
    }
  };

  
  //////////////////////////////////////////////////////////////////////////////
  // Integers use maps as it is what compiler do anyway
  //////////////////////////////////////////////////////////////////////////////
//   template<class Dummy>
//   struct  call< tag::divides_ ( tag::simd_<tag::integer_,tag::sse_>
//                               , tag::simd_<tag::integer_,tag::sse_>
//                               )
//               , tag::cpu_, Dummy
//               >
//         : call< tag::divides_ ( tag::simd_<tag::unspecified_,tag::sse_>
//                               , tag::simd_<tag::unspecified_,tag::sse_>
//                               )
//               , tag::cpu_, Dummy
//               >
//   {};
} }

#endif
