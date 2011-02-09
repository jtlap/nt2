/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_PLUS_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_PLUS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// operator binary plus
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Overload registration
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::plus_, tag::cpu_, (A0)
                      , ((simd_<double_<A0>,tag::sse_>))
                        ((simd_<double_<A0>,tag::sse_>))
                      );

NT2_REGISTER_DISPATCH ( tag::plus_, tag::cpu_, (A0)
                      , ((simd_<float_<A0>,tag::sse_>))
                        ((simd_<float_<A0>,tag::sse_>))
                      );

NT2_REGISTER_DISPATCH ( tag::plus_, tag::cpu_, (A0)
                      , ((simd_<ints8_<A0>,tag::sse_>))
                        ((simd_<ints8_<A0>,tag::sse_>))
                      );

NT2_REGISTER_DISPATCH ( tag::plus_, tag::cpu_, (A0)
                      , ((simd_<ints16_<A0>,tag::sse_>))
                        ((simd_<ints16_<A0>,tag::sse_>))
                      );

NT2_REGISTER_DISPATCH ( tag::plus_, tag::cpu_, (A0)
                      , ((simd_<ints32_<A0>,tag::sse_>))
                        ((simd_<ints32_<A0>,tag::sse_>))
                      );

NT2_REGISTER_DISPATCH ( tag::plus_, tag::cpu_, (A0)
                      , ((simd_<ints64_<A0>,tag::sse_>))
                        ((simd_<ints64_<A0>,tag::sse_>))
                      );

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::plus_( tag::simd_<tag::double_,tag::sse_>
                          , tag::simd_<tag::double_,tag::sse_>
                          )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A>  struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_add_pd(a0,a1) };
      return that;
    }
  };

  template<class Dummy>
  struct  call< tag::plus_( tag::simd_<tag::float_,tag::sse_>
                          , tag::simd_<tag::float_,tag::sse_>
                          )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A>  struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_add_ps(a0,a1) };
      return that;
    }
  };

  template<class Dummy>
  struct  call< tag::plus_( tag::simd_<tag::ints8_,tag::sse_>
                          , tag::simd_<tag::ints8_,tag::sse_>
                          )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A>  struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_add_epi8(a0,a1) };
      return that;
    }
  };

  template<class Dummy>
  struct  call< tag::plus_( tag::simd_<tag::ints16_,tag::sse_>
                          , tag::simd_<tag::ints16_,tag::sse_>
                          )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A>  struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_add_epi16(a0,a1) };
      return that;
    }
  };

  template<class Dummy>
  struct  call< tag::plus_( tag::simd_<tag::ints32_,tag::sse_>
                          , tag::simd_<tag::ints32_,tag::sse_>
                          )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A>  struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_add_epi32(a0,a1) };
      return that;
    }
  };

  template<class Dummy>
  struct  call< tag::plus_( tag::simd_<tag::ints64_,tag::sse_>
                          , tag::simd_<tag::ints64_,tag::sse_>
                          )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A>  struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_add_epi64(a0,a1) };
      return that;
    }
  };
} }

#endif
