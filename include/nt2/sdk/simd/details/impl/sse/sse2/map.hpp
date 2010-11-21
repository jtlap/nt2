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

#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#define NT2_MAP_INTERFACE(z,n,t)                                    \
template<class This,class F,class A>                                \
struct result<This(F,NT2_PP_ENUM_VALUE(n,A))> : meta::strip<A> {};  \
/**/

#define NT2_MAP_ARGS(z,n,t) BOOST_PP_CAT(a,BOOST_PP_INC(n))[t]
#define NT2_MAP_CALL(z,n,t) a0(BOOST_PP_ENUM(t,NT2_MAP_ARGS,n))

#define NT2_MAP_IMPL(z,n,t)                                             \
NT2_FUNCTOR_CALL(BOOST_PP_INC(n))                                       \
{                                                                       \
  A1 that = { BOOST_PP_TUPLE_ELEM(2,1,t)                                \
            (                                                           \
              BOOST_PP_ENUM(BOOST_PP_TUPLE_ELEM(2,0,t),NT2_MAP_CALL,n)  \
            )                                                           \
            };                                                          \
  return that;                                                          \
}                                                                       \
/**/

#define NT2_MAP_IMPL_64(z,n,t)                    \
NT2_FUNCTOR_CALL(BOOST_PP_INC(n))                 \
{                                                 \
  A1 that = {{BOOST_PP_ENUM(2,NT2_MAP_CALL,n)}};  \
  return that;                                    \
}                                                 \
/**/

namespace nt2 { namespace functors
{
  template<class Info>
  struct  call< map_  , tag::simd_(tag::arithmetic_,tag::sse_)
              , double, Info
              >
        : callable
  {
    template<class Sig> struct result;
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_INTERFACE , ~               )
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_IMPL      , (2,_mm_setr_pd) )
  };

  template<class Info>
  struct  call< map_  , tag::simd_(tag::arithmetic_,tag::sse_)
              , float , Info
              >
        : callable
  {
    template<class Sig> struct result;
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_INTERFACE , ~               )
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_IMPL      , (4,_mm_setr_ps) )
  };

  template<class Info>
  struct  call< map_  , tag::simd_(tag::arithmetic_,tag::sse_)
              , int32_, Info
              >
        : callable
  {
    template<class Sig> struct result;
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_INTERFACE , ~                 )
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_IMPL      , (4,_mm_setr_epi32))
  };

  template<class Info>
  struct  call< map_  , tag::simd_(tag::arithmetic_,tag::sse_)
              , int16_, Info
              >
        : callable
  {
    template<class Sig> struct result;
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_INTERFACE , ~                 )
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_IMPL      ,(8,_mm_setr_epi16) )
  };

  template<class Info>
  struct  call< map_  , tag::simd_(tag::arithmetic_,tag::sse_)
              , int8_ , Info
              >
        : callable
  {
    template<class Sig> struct result;
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_INTERFACE , ~                   )
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_IMPL      , (16 ,_mm_setr_epi8 ))
  };

  template<class Info>
  struct  call< map_  , tag::simd_(tag::arithmetic_,tag::sse_)
              , int64_, Info
              >
        : callable
  {
    template<class Sig> struct result;
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_INTERFACE ,~)
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_IMPL_64   ,~)
  };
} }

#undef NT2_MAP_INTERFACE
#undef NT2_MAP_ARGS
#undef NT2_MAP_CALL
#undef NT2_MAP_IMPL
#undef NT2_MAP_IMPL_64

#endif
