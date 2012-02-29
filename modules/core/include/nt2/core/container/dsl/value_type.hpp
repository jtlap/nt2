//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_VALUE_TYPE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_VALUE_TYPE_HPP_INCLUDED

#include <boost/proto/core.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/transform.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <nt2/sdk/functor/meta/call.hpp>

namespace nt2 { namespace details
{
  //==========================================================================
  // Basic generator for the usual, non-overloaded case.
  //==========================================================================
  template<class Tag, class Domain, int N, class Expr> struct value_type;
} }

namespace nt2 { namespace container
{
  namespace ext
  {
    //==========================================================================
    /*!
     * This extension point specify the type an expression actually models.
     * If most expressions model a reference to the equivalent container of their
     * domain, some may require to some other type with proper cref qualifier.
     * This meta-function enables a fine grain specification of this scheme.
     *
     * \tparam Tag    Top most tag of the expression
     * \tparam Domain Domain of the expression
     * \tparam Arity  Number of children of the expression
     * \tparam Expr   The expression itself
     *
     * \return the type modeled by the nt2::container::expression
     *
    **/
    //==========================================================================
    template<class Tag, class Domain, int N, class Expr>
    struct value_type : details::value_type<Tag, Domain, N, Expr> {};
  }
} }

namespace nt2 { namespace details
{
  //============================================================================
  // default value_type, calls meta::call on the scalar equivalent. This is the
  // case for both element-wise and reduction expression
  //============================================================================
  #define M1(z,n,t)                                                         \
  typedef typename boost::proto::result_of::child_c<Expr&, n>::type _A##n;  \
  typedef typename boost::dispatch::meta::semantic_of<_A##n>::type A##n;    \
  typedef typename boost::dispatch::meta::scalar_of<A##n>::type s##n;       \
  /**/

  #define M0(z,n,t)                                                         \
  template<class F, class Domain, class Expr>                               \
  struct value_type<F, Domain, n, Expr>                                     \
  {                                                                         \
    BOOST_PP_REPEAT(n, M1, ~)                                               \
    typedef typename meta::call<F(BOOST_PP_ENUM_PARAMS(n, s))>::type type;  \
  };                                                                        \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1, BOOST_DISPATCH_MAX_ARITY, M0, ~)

  #undef M0
  #undef M1
} }

#endif

