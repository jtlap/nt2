//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_SPECIFIC_COMMON_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_SPECIFIC_COMMON_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// By default, any SIMD implementation falls down to scalar map application if
// nothing is implemented for doing otherwise.
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/print.hpp>
#include <boost/simd/include/functions/simd/map.hpp>
#include <boost/mpl/not.hpp>
#include <boost/dispatch/meta/any.hpp>
#include <boost/proto/traits.hpp>

#ifdef BOOST_SIMD_LOG_MAP
namespace boost { namespace simd { namespace details
{
  template<class Tag>
  struct MAP_FALLBACK;
} } }
#define BOOST_SIMD_MAP_LOG(Tag) typedef typename boost::dispatch::meta::print< boost::simd::details::MAP_FALLBACK<Tag> >::type _;
#else
#define BOOST_SIMD_MAP_LOG(Tag)
#endif

#if !defined(BOOST_SIMD_DONT_USE_PREPROCESSED_FILES)
#include <boost/simd/toolbox/operator/specific/preprocessed/common.hpp>
#else
#include <boost/dispatch/details/parameters.hpp>
#include <boost/simd/sdk/functor/preprocessor/dispatch.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/common.hpp")
#undef BOOST_SIMD_MAP_LOG
#undef BOOST_FORCEINLINE
#endif

////////////////////////////////////////////////////////////////////////////////
// Register all tag and extension agnostic call for common code sharing
////////////////////////////////////////////////////////////////////////////////
#define M0(z,n,t) (A##n)
#define M1(z,n,t) (unspecified_<A##n>)

#define M2(z,n,t)                                                             \
BOOST_SIMD_REGISTER_DISPATCH_IF( elementwise_<Tag> , tag::formal_             \
                             , (Tag)BOOST_PP_REPEAT(n,M0,~)                   \
                             , (mpl::not_< any <  mpl::or_                    \
                                                  < boost::proto::            \
                                                    is_expr<mpl::_>           \
                                                  , boost::dispatch::         \
                                                    meta::is_proxy<mpl::_>    \
                                                  >                           \
                                               , BOOST_PP_ENUM_PARAMS(n,A)    \
                                               >                              \
                                          >                                   \
                                )                                             \
                             , BOOST_PP_REPEAT(n,M1,~)                        \
                             )                                                \
/**/

namespace boost { namespace simd { namespace ext
{
  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY),M2,~)
} } }

#undef M2
#undef M1
#undef M0

////////////////////////////////////////////////////////////////////////////////
// Generate all the common map calls over Tag using boost::simd::map
////////////////////////////////////////////////////////////////////////////////
#define M0(z,n,t) unspecified_<A##n>

#define M1(z,n,t)                                                              \
namespace boost { namespace simd { namespace ext                               \
{                                                                              \
  template<BOOST_PP_ENUM_PARAMS(n,class A),class Tag, class Dummy>             \
  struct implement< elementwise_<Tag>( BOOST_PP_ENUM(n,M0,~) )                 \
                  , tag::formal_, Dummy                                        \
                  >                                                            \
  {                                                                            \
    BOOST_SIMD_MAP_LOG(Tag)                                                    \
                                                                               \
    typedef typename boost::dispatch::meta::                                   \
       call<tag::map_ ( dispatch::functor<Tag>                                 \
                      , BOOST_PP_ENUM_PARAMS(n, A)                             \
                      )                                                        \
           >::type                                                             \
    result_type;                                                               \
                                                                               \
    result_type                                                                \
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const & a)) const             \
    {                                                                          \
      return boost::simd::                                                     \
             map( dispatch::functor<Tag>(), BOOST_PP_ENUM_PARAMS(n, a) );      \
    }                                                                          \
  };                                                                           \
} } }                                                                          \
/**/

BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY),M1,~)

#undef M1
#undef M0

#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

#endif
