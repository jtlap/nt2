/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_DSL_CALL_HPP_INCLUDED
#define BOOST_SIMD_SDK_DSL_CALL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// This file generate basic EDSL expression wrapper over any nt2 function
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/meta/any.hpp>
#include <boost/proto/proto.hpp>
#include <boost/simd/sdk/dsl/category.hpp>
#include <boost/dispatch/functor/functor.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/dsl/proto/as_child.hpp>
#include <boost/dispatch/functor/meta/hierarchy.hpp>

#if defined(BOOST_SIMD_DONT_USE_PREPROCESSED_FILES)
#include <boost/dispatch/extension/parameters.hpp>
#include <boost/preprocessor/selection/min.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/dispatch/functor/preprocessor/dispatch.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#endif

////////////////////////////////////////////////////////////////////////////////
// Defines the catch-all call for proto expression
////////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_SIMD_DONT_USE_PREPROCESSED_FILES)
#include <boost/simd/sdk/dsl/preprocessed/call.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/call.hpp")
#endif

#define M1(z,n,t) boost::simd::meta::as_child(BOOST_PP_CAT(a,n))
#define M2(z,n,t) (BOOST_PP_CAT(A,n))
#define M3(z,n,t) (unspecified_<BOOST_PP_CAT(A,n)>)

#define M4(z,n,t)                                                             \
BOOST_DISPATCH_REGISTER_DISPATCH_IF( Func, tag::formal_                                  \
                        , (Func)BOOST_PP_REPEAT(n,M2,~)                       \
                        , (boost::simd::meta::any< boost::proto::is_expr<boost::mpl::_>   \
                              , BOOST_PP_ENUM_PARAMS(n,A)                     \
                             >                                                \
                          )                                                   \
                      , (Func(tag::ast_))                                     \
                      , BOOST_PP_REPEAT(n,M3,~)                               \
                      )                                                       \
/**/

#define M0(z,n,t)                                                 \
template<class This,BOOST_PP_ENUM_PARAMS(n,class A)>              \
struct result<This(BOOST_PP_ENUM_PARAMS(n,A))>                    \
{                                                                 \
  typedef typename boost::proto::result_of::                      \
  make_expr < Func                                                \
            , BOOST_PP_ENUM_BINARY_PARAMS                         \
              ( n                                                 \
              , typename boost::simd::details::result_of          \
                ::as_child< typename meta::strip< A               \
              ,                                 >::type const&    \
                          >::type BOOST_PP_INTERCEPT              \
              )                                                   \
            >::type type;                                         \
};                                                                \
template<BOOST_PP_ENUM_PARAMS(n,class A)> BOOST_SIMD_FORCE_INLINE \
typename result<implement                                         \
                (BOOST_PP_ENUM_BINARY_PARAMS( n,A                 \
                                            , const&              \
                                              BOOST_PP_INTERCEPT) \
                )                                                 \
               >::type                                            \
operator()(BOOST_PP_ENUM_BINARY_PARAMS(n,A,const& a) ) const      \
{                                                                 \
  return boost::proto::                                           \
  make_expr<Func>( BOOST_PP_ENUM(n,M1,~) );                       \
}                                                                 \
/**/

namespace boost { namespace dispatch {  namespace meta
{
  BOOST_PP_REPEAT_FROM_TO ( 1
                          , BOOST_PP_INC(BOOST_PP_MIN ( BOOST_DISPATCH_MAX_ARITY
                                                      , BOOST_PROTO_MAX_ARITY
                                                      )
                                        )
                         ,M4,~
                         )

  template<class Func,class Dummy>
  struct implement<Func(tag::ast_),tag::formal_,Dummy>
  {
    template<class Sig> struct result;
    BOOST_PP_REPEAT_FROM_TO ( 1
                            , BOOST_PP_INC(BOOST_PP_MIN ( BOOST_DISPATCH_MAX_ARITY
                                                        , BOOST_PROTO_MAX_ARITY
                                                        )
                                          )
                           ,M0,~
                           )
  };
} } }

#undef M0
#undef M1
#undef M2
#undef M3
#undef M4

#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

#endif

