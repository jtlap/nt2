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

#include <boost/proto/select.hpp>
#include <boost/proto/traits.hpp>
#include <nt2/include/functor.hpp>
#include <boost/proto/transform.hpp>
#include <nt2/core/functions/extent.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <boost/dispatch/meta/transfer_qualifiers.hpp>

#include <boost/fusion/include/transform.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace container
{
  template<class T, class S>
  struct table_container;
    
  template<class Tag, int N, class Expr>
  struct size_impl;

  template<class Tag, int N, class Expr>
  struct generator_impl2;
  
  template<class Tag, int N, class Expr>
  struct generator_impl : generator_impl2<Tag, N, Expr> {};
  
  // Glue that makes generator_impl and size_impl into Proto primitive transforms
  struct generator
      : boost::proto::transform<generator>
  {
    template<class Expr, class State, class Data>
    struct impl : boost::proto::transform_impl<Expr, State, Data>
    {
      typedef generator_impl< typename boost::proto::tag_of<typename impl::expr>::type
                            , boost::proto::arity_of<typename impl::expr>::value
                            , typename impl::expr
                            >                                  function;
      typedef typename function::result_type result_type;

      BOOST_DISPATCH_FORCE_INLINE
      result_type
      operator()( typename impl::expr_param e
                , typename impl::state_param
                , typename impl::data_param
                ) const
      {
        return function()(e);
      }
    };
  };

  struct size_transform
      : boost::proto::transform<size_transform>
  {
    template<class Expr, class State, class Data>
    struct impl : boost::proto::transform_impl<Expr, State, Data>
    {
      typedef size_impl< typename boost::proto::tag_of<typename impl::expr>::type
                       , boost::proto::arity_of<typename impl::expr>::value
                       , typename impl::expr
                       >                                       function;
      typedef typename function::result_type result_type;

      BOOST_DISPATCH_FORCE_INLINE
      result_type
      operator()( typename impl::expr_param e
                , typename impl::state_param
                , typename impl::data_param
                ) const
      {
        return function()(e);
      }
    };
  };

  // table generator, computes correct scalar type and size
  #define M1(z,n,t)                                                                      \
  typedef typename boost::proto::result_of::child_c<Expr&, n>::type _A##n;               \
  typedef typename boost::dispatch::meta::semantic_of<_A##n>::type A##n;                 \
  typedef typename boost::dispatch::meta::scalar_of<A##n>::type s##n;

  #define M0(z,n,t)                                                                      \
  template<class F, class Expr>                                                          \
  struct generator_impl2<F, n, Expr>                                                     \
  {                                                                                      \
    BOOST_PP_REPEAT(n, M1, ~)                                                            \
    typedef typename meta::call<F(BOOST_PP_ENUM_PARAMS(n, s))>::type stype;              \
    typedef typename meta::                                                              \
    strip<typename size_impl<F, n, Expr>::result_type>::type       size_type;            \
    typedef typename boost::dispatch::meta::                                             \
    transfer_qualifiers< table_container< typename meta::                                \
                                          strip<stype>::type                             \
                                        , nt2::settings(size_type)                       \
                                        >                                                \
                       , stype                                                           \
                       >::type type;                                                     \
    typedef expression<Expr, type> result_type;                                          \
                                                                                         \
    BOOST_DISPATCH_FORCE_INLINE                                                          \
    result_type                                                                          \
    operator()(Expr& e) const                                                            \
    {                                                                                    \
      return result_type(e, size_impl<F, n, Expr>()(e));                                 \
    }                                                                                    \
  };

  BOOST_PP_REPEAT_FROM_TO(1, BOOST_DISPATCH_MAX_ARITY, M0, ~)
  #undef M0
  #undef M1

  // table generator terminal
  template<class Tag, class Expr>
  struct generator_impl<Tag, 0, Expr>
  {
    typedef expression< Expr
                      , typename boost::proto::result_of::
                        value<Expr&>::type
                      > result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(Expr& e) const
    {
      return result_type(e, size_impl<Tag, 0, Expr>()(e));
    }
  };

  // table generator unary function (workaround)
  template<class Expr>
  struct generator_impl<boost::proto::tag::function, 1, Expr>
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
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<0>(e);
    }
#endif
  };

  // size selection logic
  struct size_fold
  {
    template<class A0, class A1, class Dummy = void>
    struct select;

    template<class Sig>
    struct result;

    template<class This, class A0, class A1>
    struct result<This(A0, A1)>
    {
      typedef typename
      select< typename meta::strip<A0>::type
            , typename meta::strip<A1>::type
            >::type const& type;
    };

    template<class A1, class Dummy>
    struct select<_0D, A1, Dummy>
    {
      typedef A1 type;
    };
    template<class A1>
    BOOST_DISPATCH_FORCE_INLINE
    typename result<size_fold(_0D const&, A1 const&)>::type
    operator()(_0D const&, A1 const& a1) const
    {
      return a1;
    }

    template<class A0, class Dummy>
    struct select<A0, _0D, Dummy>
    {
      typedef A0 type;
    };
    template<class A0>
    BOOST_DISPATCH_FORCE_INLINE
    typename result<size_fold(A0 const&, _0D const&)>::type
    operator()(A0 const& a0, _0D const&) const
    {
      return a0;
    }

    template<class Dummy>
    struct select<_0D, _0D, Dummy>
    {
      typedef _0D type;
    };
    BOOST_DISPATCH_FORCE_INLINE
    result<size_fold(_0D const&, _0D const&)>::type
    operator()(_0D const& a0, _0D const&) const
    {
      return a0;
    }

    template<class A0, class A1, class Dummy>
    struct select
    {
      typedef A0 type;
    };
    template<class A0, class A1> BOOST_DISPATCH_FORCE_INLINE
    typename result<size_fold(A0 const&, A1 const&)>::type
    operator()(A0 const& a0, A1 const& a1) const
    {
      BOOST_ASSERT_MSG(a0 == a1, "Sizes are not compatible");
      return a0;
    }
  };

  // size computation in n-ary, nullary and unary cases
  template<class Tag, int N, class Expr>
  struct size_impl
  {
    typedef typename boost::fusion::result_of::
    transform<Expr const, size_transform>::type sizes;

    typedef typename boost::fusion::result_of::
    at_c<sizes, 0>::type init;

    typedef typename boost::fusion::result_of::
    fold<sizes, init const, size_fold>::type  result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(Expr& e) const
    {
      sizes sz = boost::fusion::transform(e, size_transform());
      return boost::fusion::fold(sz, boost::fusion::at_c<0>(sz), size_fold());
    }
  };

  template<class Tag, class Expr>
  struct size_impl<Tag, 0, Expr>
  {
    typedef typename boost::proto::result_of::
    value<Expr&>::type                                value_type;

    typedef typename meta::
    call<tag::extent_(value_type)>::type              result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(Expr& e) const
    {
      return nt2::extent(boost::proto::value(e));
    }
  };

  template<class Tag, class Expr>
  struct size_impl<Tag, 1, Expr>
  {
    typedef typename boost::proto::result_of::
    child_c<Expr&, 0>::type                         child0;

    typedef typename size_transform::template
    result<size_transform(child0)>::type            result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(Expr& e) const
    {
      return size_transform()(boost::proto::child_c<0>(e));
    }
  };
  
  // assign
  template<class Expr>
  struct generator_impl<boost::proto::tag::assign, 2, Expr>
  {
    typedef typename boost::proto::result_of::
    child_c<Expr&, 0>::type                         child0;
    
    typedef typename boost::dispatch::meta::
    semantic_of<child0>::type                       semantic;
    
    typedef typename meta::settings_of<semantic>::type                settings_type;
    typedef typename meta::option<settings_type, tag::of_size_>::type extent_type;

    typedef expression<Expr, semantic>              result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(Expr& e) const
    {
      return result_type(e, extent_type(size_transform()(boost::proto::child_c<1>(e))));
    }
  };
} }

#endif

