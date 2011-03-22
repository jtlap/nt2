/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_SPLAT_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_SPLAT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// splat for SSE2 SIMD types
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register dispatches over splat_
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::splat_, tag::cpu_, (A0)(A1)
                      , (fundamental_<A0>)
                        ((target_< simd_< double_<A1>, tag::sse_ > >))
                      )

NT2_REGISTER_DISPATCH ( tag::splat_, tag::cpu_, (A0)(A1)
                      , (fundamental_<A0>)
                        ((target_< simd_< float_<A1>, tag::sse_ > >))
                      )

NT2_REGISTER_DISPATCH ( tag::splat_, tag::cpu_, (A0)(A1)
                      , (fundamental_<A0>)
                        ((target_< simd_< ints8_<A1>, tag::sse_ > >))
                      )

NT2_REGISTER_DISPATCH ( tag::splat_, tag::cpu_, (A0)(A1)
                      , (fundamental_<A0>)
                        ((target_< simd_< ints16_<A1>, tag::sse_ > >))
                      )

NT2_REGISTER_DISPATCH ( tag::splat_, tag::cpu_, (A0)(A1)
                      , (fundamental_<A0>)
                        ((target_< simd_< ints32_<A1>, tag::sse_ > >))
                      )

NT2_REGISTER_DISPATCH ( tag::splat_, tag::cpu_, (A0)(A1)
                      , (fundamental_<A0>)
                        ((target_< simd_< ints64_<A1>, tag::sse_ > >))
                      )

////////////////////////////////////////////////////////////////////////////////
// Implements dispatches over splat_
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::splat_ ( tag::fundamental_
                            , tag::target_<tag::simd_<tag::double_,tag::sse_> >
                            )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A1>::type {};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      type that = { _mm_set1_pd(a0)  };
      return that;
    }
  };

  template<class Dummy>
  struct  call< tag::splat_ ( tag::fundamental_
                            , tag::target_<tag::simd_<tag::float_,tag::sse_> >
                            )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A1>::type {};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      type that = { _mm_set1_ps(a0)  };
      return that;
    }
  };

  template<class Dummy>
  struct  call< tag::splat_ ( tag::fundamental_
                            , tag::target_<tag::simd_<tag::ints8_,tag::sse_> >
                            )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A1>::type {};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      type that = { _mm_set1_epi8(a0)  };
      return that;
    }
  };

  template<class Dummy>
  struct  call< tag::splat_ ( tag::fundamental_
                            , tag::target_<tag::simd_<tag::ints16_,tag::sse_> >
                            )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A1>::type {};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      type that = { _mm_set1_epi16(a0)  };
      return that;
    }
  };

  template<class Dummy>
  struct  call< tag::splat_ ( tag::fundamental_
                            , tag::target_<tag::simd_<tag::ints32_,tag::sse_> >
                            )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A1>::type {};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      type that = { _mm_set1_epi32(a0)  };
      return that;
    }
  };

  template<class Dummy>
  struct  call< tag::splat_ ( tag::fundamental_
                            , tag::target_<tag::simd_<tag::ints64_,tag::sse_> >
                            )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A1>::type {};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      type that = {
          _mm_setr_epi32( (a0 & 0x00000000FFFFFFFFULL)
                        , (a0 & 0xFFFFFFFF00000000ULL) >> 32
                        , (a0 & 0x00000000FFFFFFFFULL)
                        , (a0 & 0xFFFFFFFF00000000ULL) >> 32 )
      };
      return that;
    }
  };
} }

#endif
