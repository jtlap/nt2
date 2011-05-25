/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_MAKE_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_MAKE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// splat for SSE2 SIMD types
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register dispatches over splat_
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::make_, tag::cpu_, (A0)(A1)
                      , (fundamental_<A0>)(fundamental_<A0>)
                        ((target_< simd_< double_<A1>, tag::sse_ > >))
                      )
                      
NT2_REGISTER_DISPATCH ( tag::make_, tag::cpu_, (A0)(A1)
                      , (fundamental_<A0>)(fundamental_<A0>)
                        ((target_< simd_< ints64_<A1>, tag::sse_ > >))
                      )

NT2_REGISTER_DISPATCH ( tag::make_, tag::cpu_, (A0)(A1)
                      , (fundamental_<A0>)(fundamental_<A0>)(fundamental_<A0>)(fundamental_<A0>)
                        ((target_< simd_< float_<A1>, tag::sse_ > >))
                      )
                      
NT2_REGISTER_DISPATCH ( tag::make_, tag::cpu_, (A0)(A1)
                      , (fundamental_<A0>)(fundamental_<A0>)(fundamental_<A0>)(fundamental_<A0>)
                        ((target_< simd_< ints32_<A1>, tag::sse_ > >))
                      )
                      
NT2_REGISTER_DISPATCH ( tag::make_, tag::cpu_, (A0)(A1)
                      , (fundamental_<A0>)(fundamental_<A0>)(fundamental_<A0>)(fundamental_<A0>)
                        (fundamental_<A0>)(fundamental_<A0>)(fundamental_<A0>)(fundamental_<A0>)
                        ((target_< simd_< ints16_<A1>, tag::sse_ > >))
                      )
                      
NT2_REGISTER_DISPATCH ( tag::make_, tag::cpu_, (A0)(A1)
                      , (fundamental_<A0>)(fundamental_<A0>)(fundamental_<A0>)(fundamental_<A0>)
                        (fundamental_<A0>)(fundamental_<A0>)(fundamental_<A0>)(fundamental_<A0>)
                        (fundamental_<A0>)(fundamental_<A0>)(fundamental_<A0>)(fundamental_<A0>)
                        (fundamental_<A0>)(fundamental_<A0>)(fundamental_<A0>)(fundamental_<A0>)
                        ((target_< simd_< ints8_<A1>, tag::sse_ > >))
                      )

////////////////////////////////////////////////////////////////////////////////
// Implements dispatches over splat_
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::make_ ( tag::fundamental_, tag::fundamental_
                           , tag::target_<tag::simd_<tag::double_,tag::sse_> >
                           )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1>
    struct result<This(A0,A0,A1)> : meta::strip<A1>::type {};

    NT2_FUNCTOR_CALL(3)
    {
      ignore_unused(a2);
      typedef typename NT2_RETURN_TYPE(3)::type type;
      type that = { _mm_setr_pd(a0, a1)  };
      return that;
    }
  };
  
  template<class Dummy>
  struct  call< tag::make_ ( tag::fundamental_, tag::fundamental_
                           , tag::target_<tag::simd_<tag::ints64_,tag::sse_> >
                           )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1>
    struct result<This(A0,A0,A1)> : meta::strip<A1>::type {};

    NT2_FUNCTOR_CALL(3)
    {
      ignore_unused(a2);
      typedef typename NT2_RETURN_TYPE(3)::type type;
      type that = {
          _mm_setr_epi32(
                            (uint64_t(a0) & 0x00000000FFFFFFFFULL)
                          , (uint64_t(a0) & 0xFFFFFFFF00000000ULL) >> 32
                          , (uint64_t(a1) & 0x00000000FFFFFFFFULL)
                          , (uint64_t(a1) & 0xFFFFFFFF00000000ULL) >> 32
                        )
      };
      return that;
    }
  };

  template<class Dummy>
  struct  call< tag::make_ ( tag::fundamental_, tag::fundamental_, tag::fundamental_, tag::fundamental_
                           , tag::target_<tag::simd_<tag::float_,tag::sse_> >
                           )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1>
    struct result<This(A0,A0,A0,A0,A1)> : meta::strip<A1>::type {};

    NT2_FUNCTOR_CALL(5)
    {
      ignore_unused(a4);
      typedef typename NT2_RETURN_TYPE(5)::type type;
      type that = { _mm_setr_ps(a0, a1, a2, a3)  };
      return that;
    }
  };
  
 template<class Dummy>
  struct  call< tag::make_ ( tag::fundamental_, tag::fundamental_, tag::fundamental_, tag::fundamental_
                           , tag::target_<tag::simd_<tag::ints32_,tag::sse_> >
                           )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1>
    struct result<This(A0,A0,A0,A0,A1)> : meta::strip<A1>::type {};

    NT2_FUNCTOR_CALL(5)
    {
      ignore_unused(a4);
      typedef typename NT2_RETURN_TYPE(5)::type type;
      type that = { _mm_setr_epi32(a0, a1, a2, a3)  };
      return that;
    }
  };
  
  template<class Dummy>
  struct  call< tag::make_ ( tag::fundamental_, tag::fundamental_, tag::fundamental_, tag::fundamental_
                           , tag::fundamental_, tag::fundamental_, tag::fundamental_, tag::fundamental_
                           , tag::target_<tag::simd_<tag::ints16_,tag::sse_> >
                           )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1>
    struct result<This(A0,A0,A0,A0,A0,A0,A0,A0,A1)> : meta::strip<A1>::type {};

    NT2_FUNCTOR_CALL(9)
    {
      ignore_unused(a8);
      typedef typename NT2_RETURN_TYPE(9)::type type;
      type that = { _mm_setr_epi16(a0, a1, a2, a3, a4, a5, a6, a7)  };
      return that;
    }
  };

  template<class Dummy>
  struct  call< tag::make_ ( tag::fundamental_, tag::fundamental_, tag::fundamental_, tag::fundamental_
                           , tag::fundamental_, tag::fundamental_, tag::fundamental_, tag::fundamental_
                           , tag::fundamental_, tag::fundamental_, tag::fundamental_, tag::fundamental_
                           , tag::fundamental_, tag::fundamental_, tag::fundamental_, tag::fundamental_
                           , tag::target_<tag::simd_<tag::ints8_,tag::sse_> >
                           )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1>
    struct result<This(A0,A0,A0,A0,A0,A0,A0,A0,A0,A0,A0,A0,A0,A0,A0,A0,A1)> : meta::strip<A1>::type {};

    NT2_FUNCTOR_CALL(17)
    {
      ignore_unused(a16);
      typedef typename NT2_RETURN_TYPE(17)::type type;
      type that = { _mm_setr_epi8( a0, a1,  a2,  a3,  a4,  a5,  a6,  a7
                                 , a8, a9, a10, a11, a12, a13, a14, a15
                                 )
                  };
      return that;
    }
  };

} }

#endif
