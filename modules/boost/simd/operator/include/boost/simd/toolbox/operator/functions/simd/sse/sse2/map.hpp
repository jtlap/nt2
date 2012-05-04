//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_MAP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_MAP_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/fusion/include/at.hpp>

////////////////////////////////////////////////////////////////////////////////
// Implement a SIMD map that apply a given function to any SSE vector types
// This is done by enumerating all cases of function calls over the different
// vector cardinal and function arity.
////////////////////////////////////////////////////////////////////////////////

#if !defined(BOOST_SIMD_DONT_USE_PREPROCESSED_FILES)
#include <boost/simd/toolbox/operator/functions/simd/sse/sse2/preprocessed/map.hpp>
#else
#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/map.hpp")
#undef BOOST_FORCEINLINE
#endif

#define M0(z,n,h) ((simd_< h <A##n>, boost::simd::tag::sse_ >))
#define M2(z,n,t) typename meta::scalar_of<A##n>::type
#define M3(z,n,i) fusion::at_c<i>(a##n)
#define M4(z,n,t) (A##n)
#define M5(z,n,t) f(BOOST_PP_ENUM(t, M3, n))

#define M6(z,n,t)                                                            \
namespace boost { namespace simd { namespace ext                             \
{                                                                            \
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::map_, boost::simd::tag::sse2_       \
                            , (Func)BOOST_PP_REPEAT(n, M4, ~)                \
                            , (unspecified_<Func>)                           \
                              BOOST_PP_REPEAT(n,M0,BOOST_PP_TUPLE_ELEM(2, 0, t)) \
                            )                                                \
  {                                                                          \
    typedef typename dispatch::meta::                                        \
    result_of< Func const( BOOST_PP_ENUM(n,M2,~) )                           \
             >::type                                                         \
    rtype;                                                                   \
    typedef simd::native<rtype, tag::sse_> result_type;                      \
                                                                             \
    inline result_type                                                       \
    operator()(Func const& f, BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a))   \
    {                                                                        \
      return make<result_type>(                                              \
        BOOST_PP_ENUM(BOOST_PP_TUPLE_ELEM(2, 1, t), M5, n)                   \
      );                                                                     \
    }                                                                        \
  };                                                                         \
} } }                                                                        \
/**/

#define BOOST_SIMD_MAP_CALL(T,C)                                             \
BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY),M6, (T,C) ) \
/**/

BOOST_SIMD_MAP_CALL(type64_ ,  2)
BOOST_SIMD_MAP_CALL(type32_ ,  4)
BOOST_SIMD_MAP_CALL(type16_ ,  8)
BOOST_SIMD_MAP_CALL(type8_  , 16)

#undef BOOST_SIMD_MAP_CALL
#undef M6
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
