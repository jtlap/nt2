/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_COMMON_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_COMMON_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// By default, any SIMD implementation falls down to scalar map application if
// nothing is implemented for doing otherwise.
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/sdk/functor/meta/call.hpp>
#include <boost/simd/toolbox/operator/function/map.hpp>

#if !defined(BOOST_SIMD_DONT_USE_PREPROCESSED_FILES)
#include <boost/simd/toolbox/operator/specific/preprocessed/common.hpp>
#else
#include <boost/simd/extension/parameters.hpp>
#include <boost/simd/sdk/details/preprocessor.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/common.hpp")
#endif

////////////////////////////////////////////////////////////////////////////////
// Register all tag and extension agnostic call for common code sharing
////////////////////////////////////////////////////////////////////////////////
#define M0(z,n,t) (generic_< unspecified_<A0> >)

#define M1(z,n,t)                                     \
BOOST_SIMD_REGISTER_DISPATCH ( Tag , tag::cpu_, (A0)(Tag) \
                      , BOOST_PP_REPEAT(n,M0,~)       \
                      )                               \
/**/

namespace boost { namespace simd { namespace meta
{
  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_SIMD_MAX_ARITY),M1,~)
} } }

#undef M0
#undef M1

////////////////////////////////////////////////////////////////////////////////
// Generate all the common map calls over Tag using boost::simd::map
////////////////////////////////////////////////////////////////////////////////
#define M0(z,n,t) generic_< unspecified_<BOOST_PP_CAT(A,n)> >

#define M1(z,n,t)                                                           \
namespace boost { namespace simd { namespace meta                           \
{                                                                           \
  template<BOOST_PP_ENUM_PARAMS(n,class A),class Tag, class Dummy>          \
  struct implement<Tag( BOOST_PP_ENUM(n,M0,~) ), tag::cpu_, Dummy>          \
  {                                                                         \
    typedef typename meta::call<tag::map_ ( functor<Tag>                    \
                                          , BOOST_PP_ENUM_PARAMS(n,A)       \
                                          )>::type result_type;             \
                                                                            \
    BOOST_SIMD_FUNCTOR_CALL(n)                                              \
    {                                                                       \
      return boost::simd::map( functor<Tag>(), BOOST_PP_ENUM_PARAMS(n,a));  \
    }                                                                       \
  };                                                                        \
} } }                                                                       \
/**/

BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_SIMD_MAX_ARITY),M1,~)

#undef M1
#undef M0

#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

#endif
