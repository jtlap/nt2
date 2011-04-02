//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_IS_GREATER_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_IS_GREATER_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/simd/native_cast.hpp>
#include <nt2/sdk/constant/properties.hpp>

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for double
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_greater_, tag::cpu_, (A0)
                      , ((simd_<double_<A0>,tag::sse_>))
                        ((simd_<double_<A0>,tag::sse_>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_greater_( tag::simd_<tag::double_,tag::sse_>
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
      A0 that = { _mm_cmpgt_pd(a0,a1) };
      return that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for float
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_greater_, tag::cpu_, (A0)
                      , ((simd_<float_<A0>,tag::sse_>))
                        ((simd_<float_<A0>,tag::sse_>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_greater_( tag::simd_<tag::float_,tag::sse_>
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
      A0 that = { _mm_cmpgt_ps(a0,a1) };
      return that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for unsigned types
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_greater_, tag::cpu_, (A0)
                      , ((simd_<unsigned_<A0>,tag::sse_>))
                        ((simd_<unsigned_<A0>,tag::sse_>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_greater_( tag::simd_<tag::unsigned_,tag::sse_>
                                , tag::simd_<tag::unsigned_,tag::sse_>
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
      typedef typename meta::as_integer<A0, signed>::type stype;
      stype tmp1 = simd::native_cast<stype>(a0) - Signmask<stype>();
      stype tmp2 = simd::native_cast<stype>(a1) - Signmask<stype>();
      stype tmp = nt2::gt(tmp1,tmp2);
      return simd::native_cast<A0>(tmp);
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for int8 types
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_greater_, tag::cpu_, (A0)
                      , ((simd_<int8_<A0>,tag::sse_>))
                        ((simd_<int8_<A0>,tag::sse_>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_greater_( tag::simd_<tag::int8_,tag::sse_>
                                , tag::simd_<tag::int8_,tag::sse_>
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
      A0 that = { _mm_cmpgt_epi8(a0,a1)  };
      return that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for int16 types
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_greater_, tag::cpu_, (A0)
                      , ((simd_<int16_<A0>,tag::sse_>))
                        ((simd_<int16_<A0>,tag::sse_>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_greater_( tag::simd_<tag::int16_,tag::sse_>
                                , tag::simd_<tag::int16_,tag::sse_>
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
      A0 that = { _mm_cmpgt_epi16(a0,a1)  };
      return that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for int32 types
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_greater_, tag::cpu_, (A0)
                      , ((simd_<int32_<A0>,tag::sse_>))
                        ((simd_<int32_<A0>,tag::sse_>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_greater_( tag::simd_<tag::int32_,tag::sse_>
                                , tag::simd_<tag::int32_,tag::sse_>
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
      A0 that = { _mm_cmpgt_epi32(a0,a1)  };
      return that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for int64 types
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_greater_, tag::cpu_, (A0)
                      , ((simd_<int64_<A0>,tag::sse_>))
                        ((simd_<int64_<A0>,tag::sse_>))
                      );

#if !defined(NT2_SSE2_IS_GREATER_64_DEFINED)
namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_greater_( tag::simd_<tag::int64_,tag::sse_>
                                , tag::simd_<tag::int64_,tag::sse_>
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
      typedef typename meta::downgrade<A0, signed>::type type;
      type sa0 = { a0 };
      type sa1 = { a1 };
      type al  = { _mm_shuffle_epi32(sa0, _MM_SHUFFLE(2, 2, 0, 0)) };
      type bl  = { _mm_shuffle_epi32(sa1, _MM_SHUFFLE(2, 2, 0, 0)) };
      type ah  = { _mm_shuffle_epi32(sa0, _MM_SHUFFLE(3, 3, 1, 1)) };
      type bh  = { _mm_shuffle_epi32(sa1, _MM_SHUFFLE(3, 3, 1, 1)) };

      A0 that  = { nt2::gt(ah,bh) | (nt2::eq(ah,bh) & nt2::gt(al,bl)) };
      return that;
    }
  };
} }
#endif

#endif
