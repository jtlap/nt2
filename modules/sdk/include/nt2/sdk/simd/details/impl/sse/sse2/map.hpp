/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_MAP_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_MAP_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

////////////////////////////////////////////////////////////////////////////////
// Implement a SIMD map that apply a given function to any SSE vector types
// This is done by enumerating all cases of function calls over the different
// vector cardinal and function arity. SSE specifications make it requires a
// painfull process of using mm_setr_xxx named functions depending on types
// categories. Special case is the 64 bits integers that need special care.
////////////////////////////////////////////////////////////////////////////////
#define M5(z,n,t) (BOOST_PP_CAT(A,n))
#define M4(z,n,t) BOOST_PP_CAT(a,BOOST_PP_INC(n))[t]
#define M3(z,n,t) a0(BOOST_PP_ENUM(t,M4,n))
#define M2(z,n,t) ((simd_< arithmetic_<BOOST_PP_CAT(A,BOOST_PP_INC(n))>,tag::sse_>))
#define M1(z,n,t) ,tag::simd_<tag::arithmetic_,tag::sse_>

#define M64(n,t)                                                                  \
A1 that = { _mm_setr_epi32(                                                       \
                            (uint64_t(M3(0, 0, n)) & 0x00000000FFFFFFFFULL)       \
                          , (uint64_t(M3(0, 0, n)) & 0xFFFFFFFF00000000ULL) >> 32 \
                          , (uint64_t(M3(1, 1, n)) & 0x00000000FFFFFFFFULL)       \
                          , (uint64_t(M3(1, 1, n)) & 0xFFFFFFFF00000000ULL) >> 32 \
                          )                                                       \
          }                                                                       \
/**/

#define MN64(n,t)                                           \
A1 that = { BOOST_PP_TUPLE_ELEM(4,2,t)                      \
          (                                                 \
            BOOST_PP_ENUM(BOOST_PP_TUPLE_ELEM(4,1,t),M3,n)  \
          )                                                 \
          }                                                 \
/**/

#define M0(z,n,t)                                                           \
NT2_REGISTER_DISPATCH ( tag::map_,tag::cpu_                                 \
                      , (Func)BOOST_PP_REPEAT(n,M5,t)                       \
                      , (unspecified_<Func>)                                \
                        ((simd_<BOOST_PP_TUPLE_ELEM(4,0,t)<A0>,tag::sse_>)) \
                         BOOST_PP_REPEAT(BOOST_PP_DEC(n),M2,t)              \
                      )                                                     \
namespace nt2 { namespace ext                                               \
{                                                                           \
  template<class Dummy>                                                     \
  struct call < tag::map_ ( tag::unspecified_                               \
                          , tag::simd_< tag::BOOST_PP_TUPLE_ELEM(4,0,t)     \
                                         , tag::sse_                        \
                                      >                                     \
                            BOOST_PP_REPEAT(BOOST_PP_DEC(n),M1,t)           \
                          )                                                 \
              , tag::cpu_ , Dummy> : callable                               \
  {                                                                         \
    template<class Sig> struct result;                                      \
    template<class This,class F,BOOST_PP_ENUM_PARAMS(n,class A)>            \
    struct result<This(F,BOOST_PP_ENUM_PARAMS(n,A))> : meta::strip<A0> {};  \
    NT2_FUNCTOR_CALL(BOOST_PP_INC(n))                                       \
    {                                                                       \
      BOOST_PP_TUPLE_ELEM(4,3,t)(n,t);                                      \
      return that;                                                          \
    }                                                                       \
  };                                                                        \
} }                                                                         \
/**/

#define NT2_SIMD_MAP_CALL(T,C,S,N)                      \
BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,M0, (T,C,S,N) ) \
/**/

NT2_SIMD_MAP_CALL(ints64_ ,  2 , ~              , M64 )
NT2_SIMD_MAP_CALL(double_ ,  2 , _mm_setr_pd    , MN64)
NT2_SIMD_MAP_CALL(float_  ,  4 , _mm_setr_ps    , MN64)
NT2_SIMD_MAP_CALL(ints32_ ,  4 , _mm_setr_epi32 , MN64)
NT2_SIMD_MAP_CALL(ints16_ ,  8 , _mm_setr_epi16 , MN64)
NT2_SIMD_MAP_CALL(ints8_  , 16 , _mm_setr_epi8  , MN64)

#undef NT2_SIMD_MAP_CALL
#undef MN64
#undef M64
#undef M5
#undef M4
#undef M3
#undef M2
#undef M1
#undef M0

#endif
