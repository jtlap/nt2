#ifndef BOOST_PP_IS_ITERATING
/*******************************************************************************
 *               Copyright 2010 Thomas Heller
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef BOOST_PROTO_TRANSFORM_UNPACK_HPP
#define BOOST_PROTO_TRANSFORM_UNPACK_HPP

#include <boost/proto/traits.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/proto/transform/call.hpp>
#include <boost/proto/transform/make.hpp>
#include <boost/proto/transform/impl.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace boost { namespace proto
{
  namespace detail
  {
    template< typename Fun, typename Expr
            , typename State, typename Data
            , long Arity = arity_of<Expr>::value
            >
    struct unpack_impl;

    #define BOOST_PROTO_CHILD_N(_, N, __)   proto::_child_c<N>
    #define BOOST_PROTO_CHILD_E_N(_, N, __) E(proto::_child_c<N>)

    #define BOOST_PP_ITERATION_PARAMS_1 (3, ( 1, BOOST_PROTO_MAX_ARITY, "nt2/sdk/dsl/proto/unpack.hpp"))
    #include BOOST_PP_ITERATE()

    #undef BOOST_PROTO_CHILD_N
    #undef BOOST_PROTO_CHILD_E_N
  }

  //////////////////////////////////////////////////////////////////////////////
  // unpack apply transforms on node recursively
  //////////////////////////////////////////////////////////////////////////////
  template<class Fun> struct unpack : transform< unpack<Fun> >
  {
    template<class Expr, class State, class Data>
    struct impl
        : detail::unpack_impl<Fun, Expr, State, Data>
    {};
  };

  //////////////////////////////////////////////////////////////////////////////
  // unpack is proto::callable
  //////////////////////////////////////////////////////////////////////////////
  template<class Fun> struct is_callable<unpack<Fun> > : mpl::true_ {};
}}

#endif

#else /* BOOST_PP_IS_ITERATING */

#define N BOOST_PP_ITERATION()

template<class Fun, class Expr, class State, class Data>
struct  unpack_impl<Fun, Expr, State, Data, N>
      : transform_impl<Expr, State, Data>
{
  typedef typename mpl::if_c<
          is_callable<Fun>::value
        , proto::call < Fun(BOOST_PP_ENUM(N, BOOST_PROTO_CHILD_N, _)
                      , proto::_state, proto::_data)
                      >
        , proto::make < Fun(BOOST_PP_ENUM(N, BOOST_PROTO_CHILD_N, _)
                      , proto::_state, proto::_data)
                      >
      >::type
      which;

  typedef typename
          which::template impl<Expr, State, Data>::result_type result_type;

  result_type const
  operator()(
      typename unpack_impl::expr_param e
    , typename unpack_impl::state_param s
    , typename unpack_impl::data_param d
  ) const
  {
    return typename which:: template impl<Expr, State, Data>()(e, s, d);
  }
};

template<class Fun, class E, class Expr, class State, class Data>
struct  unpack_impl<Fun(E), Expr, State, Data, N>
      : transform_impl<Expr, State, Data>
{
  typedef typename mpl::if_c<
          is_callable<Fun>::value
        , proto::call<Fun(BOOST_PP_ENUM(N, BOOST_PROTO_CHILD_E_N, _))>
        , proto::make<Fun(BOOST_PP_ENUM(N, BOOST_PROTO_CHILD_E_N, _))>
      >::type
      which;

  typedef typename which::template impl<Expr, State, Data>::result_type result_type;

  result_type const
  operator()(
      typename unpack_impl::expr_param e
    , typename unpack_impl::state_param s
    , typename unpack_impl::data_param d
  ) const
  {
      return typename which:: template impl<Expr, State, Data>()(e, s, d);
  }
};

template<class Fun, class E, class S, class Expr, class State, class Data>
struct  unpack_impl<Fun(E, S), Expr, State, Data, N>
      : transform_impl<Expr, State, Data>
{
    typedef typename mpl::if_c<
            is_callable<Fun>::value
          , proto::call<Fun(BOOST_PP_ENUM(N, BOOST_PROTO_CHILD_E_N, _), S)>
          , proto::make<Fun(BOOST_PP_ENUM(N, BOOST_PROTO_CHILD_E_N, _), S)>
        >::type
        which;

    typedef typename
            which::template impl<Expr, State, Data>::result_type result_type;

    result_type const
    operator()(
        typename unpack_impl::expr_param e
      , typename unpack_impl::state_param s
      , typename unpack_impl::data_param d
    ) const
    {
        return typename which:: template impl<Expr, State, Data>()(e, s, d);
    }
};

template<class Fun, class E, class S, class D, class Expr, class State, class Data>
struct  unpack_impl<Fun(E, S, D), Expr, State, Data, N>
      : transform_impl<Expr, State, Data>
{
    typedef typename mpl::if_c<
            is_callable<Fun>::value
          , proto::call<Fun(BOOST_PP_ENUM(N, BOOST_PROTO_CHILD_E_N, _), S, D)>
          , proto::make<Fun(BOOST_PP_ENUM(N, BOOST_PROTO_CHILD_E_N, _), S, D)>
        >::type
        which;

    typedef typename
            which::template impl<Expr, State, Data>::result_type result_type;

    result_type const
    operator()(
        typename unpack_impl::expr_param e
      , typename unpack_impl::state_param s
      , typename unpack_impl::data_param d
    ) const
    {
        return typename which:: template impl<Expr, State, Data>()(e, s, d);
    }
};

#undef N
#endif
