//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_GENERATOR_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_GENERATOR_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/meta/container_of.hpp>
#include <nt2/core/functions/extent.hpp>
#include <boost/dispatch/meta/transfer_qualifiers.hpp>
#include <boost/proto/core.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/transform.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace nt2 { namespace container { namespace ext
{    
  //////////////////////////////////////////////////////////////////////////////
  // Extension traits
  //////////////////////////////////////////////////////////////////////////////
  
  /* Size of expression, must return an of_size_,
   * by value or by const-reference */
  template<class Tag, class Domain, int N, class Expr>
  struct size;

  template<class Tag, class Domain, int N, class Expr>
  struct value_type_base;

  /* Values inside the container,
   * can be a reference */    
  template<class Tag, class Domain, int N, class Expr>
  struct value_type : value_type_base<Tag, Domain, N, Expr> {};
  
  /* Generator */
  template<class Tag, class Domain, int N, class Expr>
  struct generator;
  
  /////////////////////////////////////////////////////////////////////////////
}
  
// Glue that creates a Proto primitive transforms that applies a given trait
template<template<class Tag, class Domain, int N, class Expr> class Trait, class Domain>
struct trait_transform
    : boost::proto::transform< trait_transform<Trait, Domain> >
{
  template<class Expr, class State, class Data>
  struct impl : boost::proto::transform_impl<Expr, State, Data>
  {
    typedef Trait< typename boost::proto::tag_of<typename impl::expr>::type
                 , Domain
                 , boost::proto::arity_of<typename impl::expr>::value
                 , typename impl::expr
                 >                         function;
    typedef typename function::result_type result_type;

    BOOST_FORCEINLINE result_type
    operator()( typename impl::expr_param e
              , typename impl::state_param
              , typename impl::data_param
              ) const
    {
      return function()(e);
    }
  };
};

template<class Domain> struct generator_transform : trait_transform< ext::generator, Domain > {};
template<class Domain> struct size_transform : trait_transform< ext::size, Domain > {};
  
namespace ext
{  
  // default generator, uses value_type, size and container_of
  template<class F, class Domain, int n, class Expr>
  struct generator
  {
    typedef typename value_type<F, Domain, n, Expr>::type            stype;
  
    typedef typename meta::
    strip<typename size<F, Domain, n, Expr>::result_type>::type      size_type;

    typedef typename boost::mpl::
    if_< boost::is_same< size_type, _0D >
       , stype
       , typename boost::dispatch::meta::
         transfer_qualifiers< typename meta::container_of<Domain>::type::template
                              apply< typename meta::
                                     strip<stype>::type
                                   , nt2::settings(size_type)
                                   >::type
                            , stype
                            >::type
       >::type                                                       type;
    typedef expression<Expr, type>                                   result_type;

    BOOST_FORCEINLINE result_type
    operator()(Expr& e) const
    {
      return result_type(e, size<F, Domain, n, Expr>()(e));
    }
  };

  // default generator, terminal case
  template<class Tag, class Domain, class Expr>
  struct generator<Tag, Domain, 0, Expr>
  {
    typedef expression< Expr
                      , typename boost::proto::result_of::
                        value<Expr&>::type
                      > result_type;

    BOOST_FORCEINLINE
    result_type operator()(Expr& e) const
    {
      return result_type(e, size<Tag, Domain, 0, Expr>()(e));
    }
  };

  // generator unary function (workaround)
  template<class Domain, class Expr>
  struct generator<boost::proto::tag::function, Domain, 1, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 0>::type child0;

#if 0
    typedef typename meta::call<tag::evaluate_(child0)>::type result_type;
    result_type operator()(Expr& e) const
    {
      return nt2::evaluate(boost::proto::child_c<0>(e));
    }
#else
    typedef child0 result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<0>(e);
    }
#endif
  };
  
  // assign generator
  template<class Domain, class Expr>
  struct generator<boost::proto::tag::assign, Domain, 2, Expr>
  {
    typedef typename boost::proto::result_of::
    child_c<Expr&, 0>::type                         child0;
    
    typedef typename boost::dispatch::meta::
    semantic_of<child0>::type                       semantic;
    
    typedef typename meta::settings_of<semantic>::type                settings_type;
    typedef typename meta::option<settings_type, tag::of_size_>::type extent_type;

    typedef expression<Expr, semantic>              result_type;

    BOOST_FORCEINLINE
    result_type operator()(Expr& e) const
    {
      return result_type(e, extent_type(size_transform<Domain>()(boost::proto::child_c<1>(e))));
    }
  };
  
  /* default value_type, calls meta::call on the scalar equivalent,
   * works for element-wise and reductions */
  #define M1(z,n,t)                                                                      \
  typedef typename boost::proto::result_of::child_c<Expr&, n>::type _A##n;               \
  typedef typename boost::dispatch::meta::semantic_of<_A##n>::type A##n;                 \
  typedef typename boost::dispatch::meta::scalar_of<A##n>::type s##n;

  #define M0(z,n,t)                                                                      \
  template<class F, class Domain, class Expr>                                            \
  struct value_type_base<F, Domain, n, Expr>                                             \
  {                                                                                      \
    BOOST_PP_REPEAT(n, M1, ~)                                                            \
    typedef typename meta::call<F(BOOST_PP_ENUM_PARAMS(n, s))>::type type;               \
  };
  
  BOOST_PP_REPEAT_FROM_TO(1, BOOST_DISPATCH_MAX_ARITY, M0, ~)
  #undef M0
  #undef M1
  
  // default size, terminal case
  template<class Tag, class Domain, class Expr>
  struct size<Tag, Domain, 0, Expr>
  {
    typedef typename boost::proto::result_of::
    value<Expr&>::type                                value_type;

    typedef typename meta::
    call<tag::extent_(value_type)>::type              result_type;

    BOOST_FORCEINLINE
    result_type operator()(Expr& e) const
    {
      return nt2::extent(boost::proto::value(e));
    }
  };
  
} } }

#include <nt2/core/container/dsl/details/elementwise.hpp>

#endif

