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

#include <nt2/core/container/dsl/expression.hpp>
#include <nt2/core/container/table/table_container.hpp>
#include <nt2/include/functor.hpp>
#include <boost/dispatch/meta/transfer_qualifiers.hpp>
#include <boost/proto/select.hpp>
#include <boost/proto/transform.hpp>
#include <boost/proto/traits.hpp>

namespace nt2 { namespace container
{
  template<class F, int N>
  struct generator_impl;
  
  #define M1(z,n,t)                                                                      \
  typedef typename boost::proto::result_of::child_c<typename impl::expr, n>::type _A##n; \
  typedef typename boost::dispatch::meta::semantic_of<_A##n>::type A##n;                 \
  typedef typename meta::scalar_of<A##n>::type s##n;
  
  #define M0(z,n,t)                                                                      \
  template<class F>                                                                      \
  struct generator_impl<F, n>                                                            \
    : boost::proto::transform< generator_impl<F, n> >                                    \
  {                                                                                      \
    template<class Expr, class State, class Data>                                        \
    struct impl : boost::proto::transform_impl<Expr, State, Data>                        \
    {                                                                                    \
      BOOST_PP_REPEAT(n, M1, ~)                                                          \
      typedef typename meta::call<F(BOOST_PP_ENUM_PARAMS(n, s))>::type stype;            \
      typedef typename boost::dispatch::meta::                                           \
      transfer_qualifiers< table_container< typename meta::                              \
                                            strip<stype>::type                           \
                                          , nt2::settings()                              \
                                          >                                              \
                         , stype                                                         \
                         >::type type;                                                   \
      typedef expression<typename impl::expr, type> result_type;                         \
                                                                                         \
      BOOST_DISPATCH_FORCE_INLINE                                                        \
      result_type                                                                        \
      operator()( typename impl::expr_param e                                            \
                , typename impl::state_param s                                           \
                , typename impl::data_param d                                            \
                ) const                                                                  \
      {                                                                                  \
        return result_type(e);                                                           \
      }                                                                                  \
    };                                                                                   \
  };
  
  BOOST_PP_REPEAT_FROM_TO(1, BOOST_DISPATCH_MAX_ARITY, M0, ~)
  #undef M0
  #undef M1
   
  template<class Tag>
  struct generator_impl<Tag, 0>
      : boost::proto::transform< generator_impl<Tag, 0> >
  {
    template<class Expr, class State, class Data>
    struct impl : boost::proto::transform_impl<Expr, State, Data>
    {
      typedef expression< typename impl::expr
                        , typename boost::proto::result_of::
                          value<typename impl::expr>::type
                        > result_type;
        
      BOOST_DISPATCH_FORCE_INLINE
      result_type
      operator()( typename impl::expr_param e
                , typename impl::state_param s
                , typename impl::data_param d
                ) const
      {
        return result_type(e);
      }
    };
  };
  
  template<class Tag>
  struct tagged_generators
  {
    template<int N>
    struct case_c : generator_impl<Tag, N>
    {
    };
      
    template<class N>
    struct case_ : case_c<N::value>
    {
    };
  };

  struct generators
  {
    template<class Tag>
    struct case_
      : boost::proto::select_< tagged_generators<Tag>, boost::proto::arity_of<boost::proto::_>()>
    {
    };
  };

  struct generator
    : boost::proto::switch_<generators>
  {
  };
  
} }

#endif
 
