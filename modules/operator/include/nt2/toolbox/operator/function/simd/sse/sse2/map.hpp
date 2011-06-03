/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_MAP_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_MAP_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/toolbox/operator/specific/details/maybe_genmask.hpp>
#include <nt2/include/functions/make.hpp>

////////////////////////////////////////////////////////////////////////////////
// Implement a SIMD map that apply a given function to any SSE vector types
// This is done by enumerating all cases of function calls over the different
// vector cardinal and function arity.
////////////////////////////////////////////////////////////////////////////////

#if !defined(NT2_DONT_USE_PREPROCESSED_FILES)
#include <nt2/toolbox/operator/function/simd/sse/sse2/preprocessed/map.hpp>
#else
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#if defined(__WAVE__) && defined(NT2_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/map.hpp")
#endif

#define M6(z,n,t) typename meta::scalar_of<A##n>::type
#define M5(z,n,t) (A##n)
#define M4(z,n,t) BOOST_PP_CAT(a,BOOST_PP_INC(n))[t]
#define M3(z,n,t) details::maybe_genmask<stype>(a0(BOOST_PP_ENUM(t,M4,n)))
#define M2(z,n,t) ((simd_< arithmetic_<BOOST_PP_CAT(A,BOOST_PP_INC(n))>,tag::sse_>))
#define M1(z,n,t) ,tag::simd_<tag::arithmetic_,tag::sse_>

#define M0(z,n,t)                                                           \
NT2_REGISTER_DISPATCH ( tag::map_,tag::cpu_                                 \
                      , (Func)BOOST_PP_REPEAT(n,M5,t)                       \
                      , (unspecified_<Func>)                                \
                        ((simd_<BOOST_PP_TUPLE_ELEM(2,0,t)<A0>,tag::sse_>)) \
                         BOOST_PP_REPEAT(BOOST_PP_DEC(n),M2,t)              \
                      )                                                     \
namespace nt2 { namespace ext                                               \
{                                                                           \
  template<class Dummy>                                                     \
  struct call < tag::map_ ( tag::unspecified_                               \
                          , tag::simd_< tag::BOOST_PP_TUPLE_ELEM(2,0,t)     \
                                      , tag::sse_                           \
                                      >                                     \
                            BOOST_PP_REPEAT(BOOST_PP_DEC(n),M1,t)           \
                          )                                                 \
              , tag::cpu_ , Dummy> : callable                               \
  {                                                                         \
    template<class Sig> struct result;                                      \
    template<class This,class Func,BOOST_PP_ENUM_PARAMS(n,class A)>         \
    struct result<This(Func, BOOST_PP_ENUM_PARAMS(n,A))>                    \
    {                                                                       \
      typedef typename meta::                                               \
      result_of< typename meta::                                            \
                 strip<Func>::type const( BOOST_PP_ENUM(n,M6,~) )           \
               >::type                                                      \
      rtype;                                                                \
      typedef typename details::                                            \
      as_native< Func                                                       \
               , rtype                                                      \
               , typename meta::scalar_of<A0>::type                         \
               >::type                                                      \
      stype;                                                                \
      typedef simd::native<stype, tag::sse_> type;                          \
    };                                                                      \
                                                                            \
    NT2_FUNCTOR_CALL(BOOST_PP_INC(n))                                       \
    {                                                                       \
      typedef typename result<call(BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), A))>::type ntype;\
      typedef typename result<call(BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), A))>::stype stype;\
      return make<ntype>(BOOST_PP_ENUM(BOOST_PP_TUPLE_ELEM(2,1,t),M3,n));   \
    }                                                                       \
  };                                                                        \
} }                                                                         \
/**/

#define NT2_SIMD_MAP_CALL(T,C)                          \
BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,M0, (T,C) )     \
/**/

NT2_SIMD_MAP_CALL(ints64_ ,  2)
NT2_SIMD_MAP_CALL(double_ ,  2)
NT2_SIMD_MAP_CALL(float_  ,  4)
NT2_SIMD_MAP_CALL(ints32_ ,  4)
NT2_SIMD_MAP_CALL(ints16_ ,  8)
NT2_SIMD_MAP_CALL(ints8_  , 16)

#undef NT2_SIMD_MAP_CALL
#undef M6
#undef M5
#undef M4
#undef M3
#undef M2
#undef M1
#undef M0

#if defined(__WAVE__) && defined(NT2_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

#endif
