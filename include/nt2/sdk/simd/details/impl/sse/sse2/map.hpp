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

#define NT2_MAP_INTERFACE(z,n,t)                                          \
template<class This,class F,class A>                                      \
struct result<This(F,NT2_PP_ENUM_VALUE(n,A))> : meta::strip<A> {};        \
NT2_FUNCTOR_CALL_DISPATCH( BOOST_PP_INC(n)                                \
                         , typename nt2::meta::scalar_of<A1>::type        \
                         , (6,(double,float,int8_,int16_,int32_,int64_))  \
                         )                                                \
/**/

#define NT2_MAP_ARGS(z,n,t)     BOOST_PP_CAT(a,BOOST_PP_INC(n))[t]
#define NT2_MAP_CALL(z,n,t)     a0(BOOST_PP_ENUM(t,NT2_MAP_ARGS,n))

#define NT2_MAP_IMPL(z,n,t)                                             \
NT2_FUNCTOR_CALL_EVAL_IF(BOOST_PP_INC(n),BOOST_PP_TUPLE_ELEM(3,0,t))    \
{                                                                       \
  A1 that = { BOOST_PP_TUPLE_ELEM(3,2,t)                                \
            (                                                           \
              BOOST_PP_ENUM(BOOST_PP_TUPLE_ELEM(3,1,t),NT2_MAP_CALL,n)  \
            )                                                           \
            };                                                          \
  return that;                                                          \
}                                                                       \
/**/

#define NT2_MAP_IMPL_64(z,n,t)                    \
NT2_FUNCTOR_CALL_EVAL_IF(BOOST_PP_INC(n),int64_)  \
{                                                 \
  A1 that = {{BOOST_PP_ENUM(2,NT2_MAP_CALL,n)}};  \
  return that;                                    \
}                                                 \
/**/

namespace nt2 { namespace functors
{
  template<class Info>
  struct  call< map_        , tag::simd_(tag::arithmetic_,tag::sse_)
              , fundamental_, Info
              >
        : callable
  {
    template<class Sig> struct result;
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_INTERFACE,~)

    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_IMPL,(double,2  ,_mm_setr_pd)    )
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_IMPL,(float ,4  ,_mm_setr_ps)    )
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_IMPL,(int32_,4  ,_mm_setr_epi32) )
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_IMPL,(int16_,8  ,_mm_setr_epi16) )
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_IMPL,(int8_ ,16 ,_mm_setr_epi8 ) )
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_IMPL_64,~ )
  };
} }

#undef NT2_MAP_INTERFACE
#undef NT2_MAP_ARGS
#undef NT2_MAP_CALL
#undef NT2_MAP_IMPL
#undef NT2_MAP_IMPL_64

#endif
