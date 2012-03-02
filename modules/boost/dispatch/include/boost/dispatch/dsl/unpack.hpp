//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_DSL_UNPACK_HPP_INCLUDED
#define BOOST_DISPATCH_DSL_UNPACK_HPP_INCLUDED

#include <boost/dispatch/meta/result_of.hpp>
#include <boost/proto/traits.hpp>

#if defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)
#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/selection/min.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#endif

namespace boost { namespace dispatch
{
  template<class Expr, int N, class F0, class F1>
  struct unpack_impl;

#if !defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)
#include <boost/dispatch/dsl/preprocessed/unpack.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/unpack.hpp")
#undef BOOST_FORCEINLINE
#endif

#define M1(z, n, t) f1(boost::proto::child_c<n>(expr))
#define M2(z, n, t)                                                            \
typename boost::dispatch::meta::                                               \
         result_of< F1( typename boost::proto::result_of::                     \
                                 child_c<Expr&, n>::type                       \
                      )                                                        \
                  >::type                                                      \
/**/

#define M0(z, n, t)                                                            \
template<class Expr, class F0, class F1>                                       \
struct unpack_impl<Expr, n, F0, F1>                                            \
{                                                                              \
  typedef typename boost::dispatch::meta::                                     \
          result_of< F0( BOOST_PP_ENUM(n, M2, ~)                               \
                       )                                                       \
                   >::type                                                     \
  type;                                                                        \
  static BOOST_FORCEINLINE type                                                \
  call(Expr& expr, F0& f0, F1& f1)                                             \
  {                                                                            \
    return f0(BOOST_PP_ENUM(n, M1, ~));                                        \
  }                                                                            \
};                                                                             \
/**/
BOOST_PP_REPEAT_FROM_TO( 1
                       , BOOST_PP_INC(BOOST_PP_MIN( BOOST_DISPATCH_MAX_ARITY
                                                  , BOOST_PROTO_MAX_ARITY
                                                  )
                                     )
                       , M0
                       , ~
                       )
#undef M0
#undef M1
#undef M2

#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

  template<class Expr, class F0, class F1>
  struct unpack_impl<Expr, 0, F0, F1>
  {
    typedef typename boost::dispatch::meta::
            result_of<F0(Expr&)>::type
    type;
    static BOOST_FORCEINLINE type
    call(Expr& expr, F0& f0, F1&)
    {
      return f0(expr);
    }
  };

  template<class Expr, class F0, class F1>
  struct unpack
  {
    typedef unpack_impl<Expr, boost::proto::arity_of<Expr>::value, F0, F1> impl;
    typedef typename impl::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(Expr& expr, F0& f0, F1& f1) const
    {
      return impl::call(expr, f0, f1);
    }

    BOOST_FORCEINLINE result_type
    operator()(Expr& expr, F0& f0) const
    {
      F1 f1;
      return impl::call(expr, f0, f1);
    }

    BOOST_FORCEINLINE result_type
    operator()(Expr& expr, F1& f1) const
    {
      F0 f0;
      return impl::call(expr, f0, f1);
    }

    BOOST_FORCEINLINE result_type
    operator()(Expr& expr) const
    {
      F0 f0;
      F1 f1;
      return impl::call(expr, f0, f1);
    }
  };

  template<class Tag, class State>
  struct with_state
  {
    BOOST_FORCEINLINE
    with_state(State& state_)
     : state(state_)
    {
    }

    template<class Sig>
    struct result;

    template<class This, class Expr>
    struct result<This(Expr)>
     : dispatch::meta::call<Tag(Expr, State&)>
    {
    };

    template<class Expr>
    BOOST_FORCEINLINE typename result<with_state(Expr&)>::type
    operator()(Expr& expr) const
    {
      return typename dispatch::functor<Tag>()(expr, state);
    }

    State& state;
  };

  template<class Tag, class State, class Data>
  struct with_state_data
  {
    BOOST_FORCEINLINE
    with_state_data(State& state_, Data& data_)
     : state(state_), data(data_)
    {
    }

    template<class Sig>
    struct result;

    template<class This, class Expr>
    struct result<This(Expr)>
     : dispatch::meta::call<Tag(Expr, State&, Data&)>
    {
    };

    template<class Expr>
    BOOST_FORCEINLINE typename result<with_state_data(Expr&)>::type
    operator()(Expr& expr) const
    {
      return typename dispatch::functor<Tag>()(expr, state, data);
    }

    State& state;
    Data& data;
  };

} }

#endif
