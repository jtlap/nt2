//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_CONTAINER_TERMINAL_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_CONTAINER_TERMINAL_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <boost/fusion/include/size.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <boost/dispatch/meta/transfer_qualifiers.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/include/functions/store.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/core/container/category.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // terminal for 0-dimensional access (no-op)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::terminal_, tag::cpu_
                               , (A0)(State)(Data)
                               , (mpl::bool_< fusion::result_of::size<State>::type::value == 0 >)
                               , (ast_<unspecified_<A0> >)
                                 (fusion_sequence_<State>)
                                 (unspecified_<Data>)
                               )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_, class State_, class Data_>
    struct result<This(A0_, State_, Data_)>
    {
      typedef typename boost::dispatch::meta::
      semantic_of<A0_>::type                                     type;
    };

    template<class A0_> BOOST_FORCEINLINE
    typename result<implement(A0_&, State const&, Data const&)>::type
    operator()(A0_& a0, State const&, Data const&) const
    {
       return boost::proto::value(a0);
    }
  };

  //============================================================================
  // table terminal with a position in scalar read mode
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(S0)(State)(Data)
                            , ((ast_<table_< unspecified_<A0>, S0 > >))
                              (fusion_sequence_<State>)
                              (target_<scalar_<unspecified_<Data> > >)
                            )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_, class State_, class Data_>
    struct result<This(A0_, State_, Data_)>
    {
      typedef typename boost::dispatch::meta::
      scalar_of< typename boost::dispatch::meta::
                 semantic_of<A0_>::type
                >::type                                     type;
    };

    template<class A0_> BOOST_FORCEINLINE
    typename result<implement(A0_&, State const&, Data const&)>::type
    operator()(A0_& a0, State const& state, Data const&) const
    {
       return boost::proto::value(a0)[state];
    }
  };

  //============================================================================
  // table terminal with a position in scalar write mode
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(S0)(State)(Data)
                            , ((ast_<table_< unspecified_<A0>, S0 > >))
                              (fusion_sequence_<State>)
                              (scalar_<unspecified_<Data> >)
                            )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_, class State_, class Data_>
    struct result<This(A0_, State_, Data_)>
    {
      typedef typename boost::dispatch::meta::
      scalar_of< typename boost::dispatch::meta::
                 semantic_of<A0_>::type
               >::type                                     type;
    };

    template<class A0_> BOOST_FORCEINLINE
    typename result<implement(A0_&, State const&, Data const&)>::type
    operator()(A0_& a0, State const& state, Data const& data) const
    {
       return boost::proto::value(a0)[state] = data;
    }
  };

  //============================================================================
  // table terminal with a position in SIMD read mode
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(S0)(State)(Data)(X)
                            , ((ast_<table_< unspecified_<A0>, S0 > >))
                              (fusion_sequence_<State>)
                              ((target_< simd_<unspecified_<Data>, X> >))
                            )
  {
    typedef typename Data::type                                  result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, State const& state, Data const&) const
    {
      return load<result_type>(&boost::proto::value(a0)[state]);
    }
  };

  //============================================================================
  // table terminal with a position in SIMD write mode
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(S0)(State)(Data)(X)
                            , ((ast_<table_< unspecified_<A0>, S0 > >))
                              (fusion_sequence_<State>)
                              ((simd_<unspecified_<Data>, X>))
                            )
  {
    typedef Data                                                 result_type;

    template<class A0_>
    BOOST_FORCEINLINE
    result_type operator()(A0_& a0, State const& state, Data const& data) const
    {
      return store(data, &boost::proto::value(a0)[state]);
    }
  };

  //============================================================================
  // scalar terminal, return value in scalar mode (LHS not allowed)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((ast_<scalar_< unspecified_<A0> > >))
                              (fusion_sequence_<State>)
                              (target_< scalar_< unspecified_<Data> > >)
                            )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_, class State_, class Data_>
    struct result<This(A0_, State_, Data_)>
    {
      typedef typename boost::dispatch::meta::
      semantic_of<A0_>::type                                     type;
    };

    template<class A0_> BOOST_FORCEINLINE
    typename result<implement(A0_&, State const&, Data const&)>::type
    operator()(A0_& a0, State const&, Data const&) const
    {
       return boost::proto::value(a0);
    }
  };

  //============================================================================
  // scalar terminal, splat value in SIMD read mode (LHS not allowed)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(State)(Data)(X)
                            , ((ast_<scalar_< unspecified_<A0> > >))
                              (fusion_sequence_<State>)
                              ((target_< simd_< unspecified_<Data>,X > >))
                            )
  {
    typedef typename Data::type   result_type;

    template<class A0_> BOOST_FORCEINLINE
    result_type operator()(A0_& a0, State const&, Data const&) const
    {
      return nt2::splat<result_type>(boost::proto::value(a0));
    }
  };
} }

#endif
