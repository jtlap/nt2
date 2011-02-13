//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE4_1_IS_EQUAL_TO_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE4_1_IS_EQUAL_TO_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for ints64
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_equal_, tag::cpu_, (A0)
                      , ((simd_<ints64_<A0>,tag::sse_>))
                        ((simd_<ints64_<A0>,tag::sse_>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_equal_( tag::simd_<tag::ints64_,tag::sse_>
                              , tag::simd_<tag::ints64_,tag::sse_>
                              )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_cmpeq_epi64(a0,a1) };
      return that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Reuse SSE2 implementation for the other
////////////////////////////////////////////////////////////////////////////////
#define NT2_SSE2_IS_EQUAL_64_DEFINED
#include <nt2/sdk/simd/details/impl/sse/sse2/is_equal_to.hpp>
#undef NT2_SSE2_IS_EQUAL_64_DEFINED

#endif

