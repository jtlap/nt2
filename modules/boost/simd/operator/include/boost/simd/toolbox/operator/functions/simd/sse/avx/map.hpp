//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_MAP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_MAP_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>

////////////////////////////////////////////////////////////////////////////////
// Implement a SIMD map that apply a given function to any AVX vector types
// This is done by splitting it into 2 SSE vector and calling the functor
// again
////////////////////////////////////////////////////////////////////////////////

#if !defined(BOOST_SIMD_DONT_USE_PREPROCESSED_FILES)
#include <boost/simd/toolbox/operator/functions/simd/sse/avx/preprocessed/map.hpp>
#else
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/map.hpp")
#endif

#define M0(z,n,h) ((simd_< h <A##n>, boost::simd::tag::avx_ >))
#define M1(z,n,t) simd::native<typename meta::scalar_of<A##n>::type, tag::sse_>
#define M2(z,n,t) (A##n)

#define M3(z,n,t)                                                              \
native<typename meta::scalar_of<A##n>::type,tag::sse_> a##0##n,a##1##n;        \
/**/

#define M4(z,n,t)                         \
a##0##n = _mm256_extractf128_##t(a##n,0); \
a##1##n = _mm256_extractf128_##t(a##n,1); \
/**/

#define M5(z,n,t)                                                              \
namespace boost { namespace simd { namespace ext                               \
{                                                                              \
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION                                            \
  ( boost::simd::tag::map_, boost::simd::tag::avx_                             \
  , (Func)BOOST_PP_REPEAT(n, M2, ~)                                            \
  , (unspecified_<Func>)                                                       \
    BOOST_PP_REPEAT(n,M0,BOOST_PP_TUPLE_ELEM(2, 0, t))                         \
  )                                                                            \
  {                                                                            \
    typedef typename dispatch::meta::                                          \
    result_of< Func const( BOOST_PP_ENUM(n,M1,~) )>::type base;                \
                                                                               \
    typedef simd::native< typename meta::scalar_of<base>::type                 \
                        , boost::simd::tag::avx_> result_type;                 \
                                                                               \
    inline result_type                                                         \
    operator()( Func const& f                                                  \
              , BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a)                    \
              ) const                                                          \
    {                                                                          \
      base r0,r1;                                                              \
      result_type that;                                                        \
      BOOST_PP_REPEAT(n, M3, ~)                                                \
      BOOST_PP_REPEAT(n, M4, BOOST_PP_TUPLE_ELEM(2, 1, t))                     \
      r0 = f(BOOST_PP_ENUM_PARAMS(n, a0) );                                    \
      r1 = f(BOOST_PP_ENUM_PARAMS(n, a1) );                                    \
      that                                                                     \
      = BOOST_PP_CAT(_mm256_insertf128_,BOOST_PP_TUPLE_ELEM(2,1,t))            \
        (that(),r0(),0);                                                       \
      that                                                                     \
      = BOOST_PP_CAT(_mm256_insertf128_,BOOST_PP_TUPLE_ELEM(2,1,t))            \
        (that(),r1(),1);                                                       \
      return that;                                                             \
    }                                                                          \
  };                                                                           \
} } }                                                                          \
/**/

#define BOOST_SIMD_MAP_CALL(T,C)                                               \
BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY),M5, (T,C))    \
/**/

BOOST_SIMD_MAP_CALL(double_ , pd    )
BOOST_SIMD_MAP_CALL(single_  , ps    )
BOOST_SIMD_MAP_CALL(integer_, si256 )

#undef BOOST_SIMD_MAP_CALL
#undef M5
#undef M4
#undef M3
#undef M2
#undef M1
#undef M0

#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

#endif
#endif
