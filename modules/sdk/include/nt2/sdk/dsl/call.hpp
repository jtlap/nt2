/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_CALL_HPP_INCLUDED
#define NT2_SDK_DSL_CALL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// This file generate basic EDSL expression wrapper over any nt2 function
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/any.hpp>
#include <boost/proto/proto.hpp>
#include <nt2/sdk/dsl/category.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/extension/parameters.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/hierarchy.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Defines the catch-all call for proto expression
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace details
{
    template<typename Expr, typename Enable = void>
    struct is_terminal : boost::mpl::false_
    {
    };

    template<typename Expr>
    struct is_terminal< Expr
                      , typename boost::
                        enable_if< boost::is_same< typename boost::proto::tag_of<Expr>::type
                                                 , boost::proto::tag::terminal
                                                 >
                                 >::type
                      >
      : boost::mpl::true_
    {
    };

    
    namespace result_of
    {
        template<typename Expr, typename Enable = void>
        struct as_child
          : nt2::meta::strip<Expr>
        {
        };

        template<typename Expr>
        struct as_child<Expr, typename boost::enable_if< is_terminal<Expr> >::type>
        {
            typedef Expr& type;
        };
    }

    template<typename Expr>
    typename boost::disable_if<
        is_terminal<Expr>,
        Expr
    >::type
    as_child(Expr const& expr)
    {
        return expr;
    }

    template<typename Expr>
    typename boost::enable_if<
        is_terminal<Expr>,
        boost::reference_wrapper<Expr>
    >::type
    as_child(Expr& expr)
    {
        return boost::ref(expr);
    }

    template<typename Expr>
    typename boost::enable_if<
        is_terminal<Expr>,
        boost::reference_wrapper<Expr const>
    >::type
    as_child(Expr const& expr)
    {
        return boost::cref(expr);
    }

} }

#if !defined(NT2_DONT_USE_PREPROCESSED_FILES)
#include <nt2/sdk/dsl/preprocessed/call.hpp>
#else
#if defined(__WAVE__) && defined(NT2_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/call.hpp")
#endif

#define M1(z,n,t) nt2::details::as_child(BOOST_PP_CAT(a,n))
#define M2(z,n,t) (BOOST_PP_CAT(A,n))
#define M3(z,n,t) (unspecified_<BOOST_PP_CAT(A,n)>)

#define M4(z,n,t)                                                             \
NT2_REGISTER_DISPATCH_IF( Func, tag::formal_                                  \
                        , (Func)BOOST_PP_REPEAT(n,M2,~)                       \
                        , (any< boost::proto::is_expr<boost::mpl::_>          \
                              , BOOST_PP_ENUM_PARAMS(n,A)                     \
                             >                                                \
                          )                                                   \
                      , (Func(tag::ast_))                                     \
                      , BOOST_PP_REPEAT(n,M3,~)                               \
                      )                                                       \
/**/

#define M0(z,n,t)                                               \
template<class This,BOOST_PP_ENUM_PARAMS(n,class A)>            \
struct result<This(BOOST_PP_ENUM_PARAMS(n,A))>                  \
{                                                               \
  typedef typename boost::proto::result_of::                    \
  make_expr < Func                                              \
            , BOOST_PP_ENUM_BINARY_PARAMS                       \
              ( n                                               \
              , typename nt2::details::result_of                \
                ::as_child< typename meta::strip< A             \
              ,                                 >::type const&  \
                          >::type BOOST_PP_INTERCEPT            \
              )                                                 \
            >::type type;                                       \
};                                                              \
NT2_FUNCTOR_CALL(n)                                             \
{                                                               \
  return boost::proto::                                         \
  make_expr<Func>( BOOST_PP_ENUM(n,M1,~) );                     \
}                                                               \
/**/

BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_PROTO_MAX_ARITY),M4,~)
namespace nt2 { namespace ext
{
  template<class Func,class Dummy>
  struct call<Func(tag::ast_),tag::formal_,Dummy> : callable
  {
    template<class Sig> struct result;
    BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_PROTO_MAX_ARITY),M0,~)
  };
} }

#undef M0
#undef M1
#undef M2
#undef M3
#undef M4

#if defined(__WAVE__) && defined(NT2_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

#endif

