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

#include <boost/simd/toolbox/operator/functions/map.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>

////////////////////////////////////////////////////////////////////////////////
// Implements a SIMD map that applies a given function to any AVX vector type.
// This is done by splitting it into 2 SSE vectors calling the functor on each
// and merging the two results.
////////////////////////////////////////////////////////////////////////////////

// map_avx_sse is used to merge two SSE vectors into a single AVX one
namespace boost { namespace simd
{
  namespace tag
  {
    struct map_avx_sse_ : dispatch::tag::formal_ { typedef dispatch::tag::formal_ parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::map_avx_sse_, map_avx_sse, 2)
} }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION
  ( boost::simd::tag::map_avx_sse_, boost::simd::tag::avx_
  , (A0)
  , ((simd_< logical_<A0>, boost::simd::tag::sse_ >))
    ((simd_< logical_<A0>, boost::simd::tag::sse_ >))
  )
  {
    typedef simd::native< typename meta::scalar_of<A0>::type
                        , boost::simd::tag::avx_
                        > result_type;

    inline result_type
    operator()(A0 const& a0, A0 const& a1) const
    {
      typedef typename A0::type arith_t;
      return bitwise_cast<result_type>(
        map_avx_sse( bitwise_cast<arith_t>(a0), bitwise_cast<arith_t>(a1) )
      );
    }
  };
} } }

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
#undef BOOST_FORCEINLINE
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
    BOOST_PP_REPEAT(n,M0,BOOST_PP_TUPLE_ELEM(3, 0, t))                         \
  )                                                                            \
  {                                                                            \
    typedef typename dispatch::meta::                                          \
    result_of< Func const( BOOST_PP_ENUM(n,M1,~) )>::type base;                \
                                                                               \
    typedef simd::native< typename meta::scalar_of<base>::type                 \
                        , boost::simd::tag::avx_                               \
                        > result_type;                                         \
                                                                               \
    inline result_type                                                         \
    operator()( Func const& f                                                  \
              , BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a)                    \
              ) const                                                          \
    {                                                                          \
      base r0,r1;                                                              \
      BOOST_PP_REPEAT(n, M3, ~)                                                \
      BOOST_PP_REPEAT(n, M4, BOOST_PP_TUPLE_ELEM(3, 1, t))                     \
      r0 = f(BOOST_PP_ENUM_PARAMS(n, a0) );                                    \
      r1 = f(BOOST_PP_ENUM_PARAMS(n, a1) );                                    \
      return map_avx_sse(r0, r1);                                                \
    }                                                                          \
  };                                                                           \
} } }                                                                          \
/**/

#define BOOST_SIMD_MAP_CALL(T,C,CC)                                            \
namespace boost { namespace simd { namespace ext                               \
{                                                                              \
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION                                            \
  ( boost::simd::tag::map_avx_sse_, boost::simd::tag::avx_                       \
  , (A0)                                                                       \
  , ((simd_< T<A0>, boost::simd::tag::sse_ >))                                 \
    ((simd_< T<A0>, boost::simd::tag::sse_ >))                                 \
  )                                                                            \
  {                                                                            \
    typedef simd::native< typename meta::scalar_of<A0>::type                   \
                        , boost::simd::tag::avx_                               \
                        > result_type;                                         \
                                                                               \
    inline result_type                                                         \
    operator()(A0 const& a0, A0 const& a1) const                               \
    {                                                                          \
      result_type that = BOOST_PP_CAT(_mm256_cast, CC)(a0());                  \
                  that = BOOST_PP_CAT(_mm256_insertf128_, C)(that(), a1(), 1); \
      return that;                                                             \
    }                                                                          \
  };                                                                           \
} } }                                                                          \
BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY),M5,(T,C,CC))  \
/**/

BOOST_SIMD_MAP_CALL(double_ , pd    , pd128_pd256 )
BOOST_SIMD_MAP_CALL(single_ , ps    , ps128_ps256 )
BOOST_SIMD_MAP_CALL(integer_, si256 , si128_si256 )

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
