//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_IS_LESS_EQUAL_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_IS_LESS_EQUAL_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for double
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_less_equal_, tag::cpu_, (A0)
                      , ((simd_<double_<A0>,tag::sse_>))
                        ((simd_<double_<A0>,tag::sse_>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_less_equal_ ( tag::simd_<tag::double_,tag::sse_>
                                    , tag::simd_<tag::double_,tag::sse_>
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
      A0 that = { _mm_cmple_pd(a0,a1) };
      return that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for float
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_less_equal_, tag::cpu_, (A0)
                      , ((simd_<float_<A0>,tag::sse_>))
                        ((simd_<float_<A0>,tag::sse_>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_less_equal_ ( tag::simd_<tag::float_,tag::sse_>
                                    , tag::simd_<tag::float_,tag::sse_>
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
      A0 that = { _mm_cmple_ps(a0,a1) };
      return that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for integers
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_less_equal_, tag::cpu_, (A0)
                      , ((simd_<integer_<A0>,tag::sse_>))
                        ((simd_<integer_<A0>,tag::sse_>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_less_equal_ ( tag::simd_<tag::integer_,tag::sse_>
                                    , tag::simd_<tag::integer_,tag::sse_>
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
      A0 that = { nt2::complement(nt2::gt(a0,a1)) };
      return that;
    }
  };
} }

#endif
