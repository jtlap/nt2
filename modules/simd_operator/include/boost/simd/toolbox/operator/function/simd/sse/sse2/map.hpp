//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_MAP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_MAP_HPP_INCLUDED

#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/toolbox/operator/specific/details/maybe_genmask.hpp>
#include <boost/simd/include/functions/make.hpp>

////////////////////////////////////////////////////////////////////////////////
// Implement a SIMD map that apply a given function to any SSE vector types
// This is done by enumerating all cases of function calls over the different
// vector cardinal and function arity.
////////////////////////////////////////////////////////////////////////////////

#if !defined(BOOST_SIMD_DONT_USE_PREPROCESSED_FILES)
#include <boost/simd/toolbox/operator/function/simd/sse/sse2/preprocessed/map.hpp>
#else
#include <boost/dispatch/extension/parameters.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/map.hpp")
#endif

#define M6(z,n,t) typename meta::scalar_of<BOOST_PP_CAT(A,BOOST_PP_INC(n))>::type
#define M5(z,n,t) (BOOST_PP_CAT(A,n))
#define M4(z,n,t) BOOST_PP_CAT(a,BOOST_PP_INC(n))[t]
#define M3(z,n,t) boost::simd::details::maybe_genmask<stype>(a0(BOOST_PP_ENUM(t,M4,n)))
#define M2(z,n,t) ((simd_< arithmetic_<BOOST_PP_CAT(A,BOOST_PP_INC(BOOST_PP_INC(n)))>,boost::simd::tag::sse_>))
#define M1(z,n,t) ,boost::simd::tag::simd_<tag::arithmetic_,boost::simd::tag::sse_>

#define M0(z,n,t)                                                                   \
namespace boost { namespace dispatch { namespace meta                                   \
{                                                                                   \
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( boost::simd::tag::map_,tag::cpu_                            \
                            , BOOST_PP_REPEAT(BOOST_PP_INC(n),M5,t)                 \
                            , (unspecified_<A0>)                                    \
                              ((simd_< BOOST_PP_TUPLE_ELEM(2,0,t)<A1>,boost::simd::tag::sse_>))  \
                              BOOST_PP_REPEAT(BOOST_PP_DEC(n),M2,t)                 \
                            )                                                       \
  {                                                                                 \
    typedef typename meta::                                                         \
      result_of< typename meta::                                                    \
                 strip<A0>::type const( BOOST_PP_ENUM(n,M6,~) )                     \
               >::type                                                              \
      rtype;                                                                        \
      typedef typename boost::simd::details::                                       \
      as_native< A0                                                                 \
               , rtype                                                              \
               , typename meta::scalar_of<A1>::type                                 \
               >::type                                                              \
      stype;                                                                        \
      typedef boost::simd::native<stype, boost::simd::tag::sse_> result_type;                           \
                                                                                    \
    BOOST_DISPATCH_FUNCTOR_CALL(BOOST_PP_INC(n))                                        \
    {                                                                               \
      return boost::simd::make<result_type>(BOOST_PP_ENUM(BOOST_PP_TUPLE_ELEM(2,1,t),M3,n));     \
    }                                                                               \
  };                                                                                \
} } }                                                                               \
/**/

#define BOOST_SIMD_MAP_CALL(T,C)                          \
BOOST_PP_REPEAT_FROM_TO(1,BOOST_DISPATCH_MAX_ARITY,M0, (T,C) )     \
/**/

BOOST_SIMD_MAP_CALL(ints64_ ,  2)
BOOST_SIMD_MAP_CALL(double_ ,  2)
BOOST_SIMD_MAP_CALL(float_  ,  4)
BOOST_SIMD_MAP_CALL(ints32_ ,  4)
BOOST_SIMD_MAP_CALL(ints16_ ,  8)
BOOST_SIMD_MAP_CALL(ints8_  , 16)

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
