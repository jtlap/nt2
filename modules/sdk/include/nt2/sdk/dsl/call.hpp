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
#include <nt2/extension/parameters.hpp>

////////////////////////////////////////////////////////////////////////////////
// Generate up to NT2_MAX_ARITY dispacth registration. If at least one parameter
// is a proto expression, send the dispatch into call<F(ast_)>
////////////////////////////////////////////////////////////////////////////////
#define M2(z,n,t) (BOOST_PP_CAT(A,n))
#define M1(z,n,t) (unspecified_<BOOST_PP_CAT(A,n)>)
#define M0(z,n,t)                                                             \
NT2_REGISTER_DISPATCH_IF( Func, tag::cpu_                                     \
                        , (Func)BOOST_PP_REPEAT(n,M2,~)                       \
                        , (any< boost::proto::is_expr<boost::mpl::_>          \
                              , BOOST_PP_ENUM_PARAMS(n,A)                     \
                             >                                                \
                          )                                                   \
                      , (Func(tag::ast_))                                     \
                      , BOOST_PP_REPEAT(n,M1,~)                               \
                      )                                                       \
/**/

BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M0,~)

#undef M0
#undef M1
#undef M2

////////////////////////////////////////////////////////////////////////////////
// Defines the catch-all call for proto expression
////////////////////////////////////////////////////////////////////////////////
#define M1(z,n,t) boost::cref(BOOST_PP_CAT(a,n))

#define M0(z,n,t)                                     \
template<class This,BOOST_PP_ENUM_PARAMS(n,class A)>  \
struct result<This(BOOST_PP_ENUM_PARAMS(n,A))>        \
{                                                     \
  typedef typename boost::proto::result_of::          \
  make_expr < Func                                    \
            , BOOST_PP_ENUM_BINARY_PARAMS             \
              ( n                                     \
              , typename meta::strip<A                \
              , >::type const& BOOST_PP_INTERCEPT     \
              )                                       \
            >::type type;                             \
};                                                    \
NT2_FUNCTOR_CALL(n)                                   \
{                                                     \
  return boost::proto::                               \
  make_expr<Func>( BOOST_PP_ENUM(n,M1,~) );           \
}                                                     \
/**/

namespace nt2 { namespace ext
{
  template<class Func,class Dummy>
  struct call<Func(tag::ast_),tag::cpu_,Dummy> : callable
  {
    template<class Sig> struct result;
    BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M0,~)
  };
} }

#undef M0
#undef M1

#endif
