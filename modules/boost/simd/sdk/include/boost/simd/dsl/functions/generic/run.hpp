//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_GENERIC_RUN_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_GENERIC_RUN_HPP_INCLUDED

#include <boost/simd/dsl/functions/run.hpp>
#include <boost/dispatch/dsl/unpack.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/simd/include/functions/terminal.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as.hpp>

namespace boost { namespace simd { namespace ext
{
  /* Adapt Data with Expr whenever it is a target */
  template<class Expr, class Data>
  struct adapt_data
  {
    typedef Data type;
    BOOST_FORCEINLINE static type const& call(Data const& data)
    {
      return data;
    }
  };

  template<class Expr, class Data>
  struct adapt_data< Expr, boost::dispatch::meta::as_<Data> >
  {
    typedef typename meta::scalar_of<Expr>::type stype;
    typedef typename boost::dispatch::meta::strip<stype>::type sstype;
    typedef boost::dispatch::meta::as_<sstype> type;
    BOOST_FORCEINLINE static type call(boost::dispatch::meta::as_<Data> const&)
    {
      return type();
    }
  };

  template<class Expr, class T, class X>
  struct adapt_data< Expr, boost::dispatch::meta::as_< boost::simd::native<T, X> > >
  {
    typedef typename meta::scalar_of<Expr>::type stype;
    typedef typename boost::dispatch::meta::strip<stype>::type sstype;
    typedef boost::dispatch::meta::as_< boost::simd::native<sstype, X> > type;
    BOOST_FORCEINLINE static type call(boost::dispatch::meta::as_< boost::simd::native<T, X> > const&)
    {
      return type();
    }
  };

  /* Run with state and data adapts the data each time depending on the
   * resulting semantic */
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
     : dispatch::meta::
       call<Tag( Expr
               , State&
               , typename adapt_data< typename boost::dispatch::meta::
                                      strip<Expr>::type
                                    , typename boost::dispatch::meta::
                                      strip<Data>::type
                                    >::type
               )
           >
    {
    };

    template<class Expr>
    BOOST_FORCEINLINE typename result<with_state_data(Expr&)>::type
    operator()(Expr& expr) const
    {
      return typename dispatch::functor<Tag>()
             ( expr
             , state
             , adapt_data< typename boost::dispatch::meta::
                           strip<Expr>::type
                         , typename boost::dispatch::meta::
                           strip<Data>::type
                         >::call(data)
             );
    }

    State& state;
    Data& data;
  };

  //============================================================================
  // Run an expression without state nor data
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::run_, tag::formal_
                                    , (A0)
                                    , (ast_<A0>)
                                    )
  {
    typedef dispatch::
            unpack< A0
                  , dispatch::functor< typename proto::tag_of<A0>::type >
                  , typename dispatch::make_functor<tag::run_, A0>::type
                  >
    transform;

    typedef typename transform::result_type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0) const
    {
      return transform()(a0);
    }
  };

  //============================================================================
  // Run an expression with a state and a data
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::run_, tag::cpu_
                                    , (A0)(State)(Data)
                                    , (ast_<A0>)
                                      (unspecified_<State>)
                                      (unspecified_<Data>)
                                    )
  {
    typedef dispatch::
            unpack< A0
                  , dispatch::functor< typename proto::tag_of<A0>::type >
                  , with_state_data<tag::run_, State const, Data const> const
                  >
    transform;

    typedef typename transform::result_type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, State const& state, Data const& data) const
    {
       return transform()(a0, with_state_data<tag::run_, State const, Data const>(state, data));
    }
  };

  //============================================================================
  // Run an expression with a state and data - Terminal cases
  // When run on a terminal, we directly jump into the terminal functor
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::run_, tag::cpu_
                                    , (A0)(T)
                                    , ((expr_ < unspecified_<A0>
                                              , T
                                              , mpl::long_<0>
                                              >
                                      ))
                                    )
  {
    typedef typename dispatch::meta::
            call<T(A0&)>::type  result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0) const
    {
      return typename dispatch::make_functor<T, A0>::type()
                      (a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::run_, tag::cpu_
                                    , (A0)(T)(State)(Data)
                                    , ((expr_ < unspecified_<A0>
                                              , T
                                              , mpl::long_<0>
                                              >
                                      ))
                                      (unspecified_<State>)
                                      (unspecified_<Data>)
                                    )
  {
    typedef typename dispatch::meta::
            call<T(A0&, State const&, Data const&)>::type  result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, State const& state, Data const& data) const
    {
      return typename dispatch::make_functor<T, A0>::type()
                      (a0, state, data);
    }
  };
} } }

#endif
