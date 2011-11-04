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
#include <nt2/toolbox/operator/functions/splat.hpp>

namespace nt2 { namespace ext
{
  // terminal for 0-dimensional access
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::terminal_, tag::cpu_
                               , (A0)(State)(Data)
                               , (mpl::bool_< fusion::result_of::size<State>::type::value == 0 >)
                               , (ast_<unspecified_<A0> >)
                                 (fusion_sequence_<State>)
                                 (unspecified_<Data>)
                               )
  {
    typedef typename boost::dispatch::meta::semantic_of<A0>::type result_type;

    template<class A0_> BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(A0_& a0, _0D const&, Data const&) const
    {
       return boost::proto::value(a0);
    }
  };

  //============================================================================
  // table terminal with a position in scalar mode
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(S0)(State)(Data)
                            , ((ast_<table_< unspecified_<A0>, S0 > >))
                              (fusion_sequence_<State>)
                              (target_< unspecified_<Data> >)
                            )
  {
    template<class Sig> struct result;

    template<class This, class A0_, class S_, class D_>
    struct result<This(A0_,S_,D_)>
    {
      //========================================================================
      // This type computation generates the type returned by the evaluation
      // of a terminal at a given position. This is done through reinterpreting
      // a given position in a table as a reference to the potentially SIMD type
      // required to make it work.
      //========================================================================
      typedef typename  boost::proto::result_of::value<A0_&>::type   value_type;
      typedef typename  boost::dispatch::meta::strip<D_>::type      data_type;
      typedef typename  data_type::type                             target_type;
      typedef typename  boost::dispatch::meta::
                        transfer_qualifiers<target_type,value_type>::type  qualif_type;
      typedef typename boost::add_reference<qualif_type>::type      type;
    };

    template<class A0_> BOOST_DISPATCH_FORCE_INLINE
    typename result<implement(A0_&,State,Data)>::type
    operator()(A0_& a0, State const& state, Data const&) const
    {
      typedef typename result<implement(A0_&,State,Data)>::type type;
      return reinterpret_cast<type>(boost::proto::value(a0)(state));
    }
  };

  //============================================================================
  // scalar terminal, return value in scalar mode
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((ast_<scalar_< unspecified_<A0> > >))
                              (fusion_sequence_<State>)
                              (target_< scalar_< unspecified_<Data> > >)
                            )
  {
    typedef typename boost::dispatch::meta::
    scalar_of< typename boost::dispatch::meta::
               semantic_of<A0>::type
             >::type                                       result_type;

    template<class A0_> BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(A0_& a0, State const& state, Data const&) const
    {
       return boost::proto::value(a0);
    }
  };

  //============================================================================
  // scalar terminal, splat value in SIMD mode
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(State)(Data)(X)
                            , ((ast_<scalar_< unspecified_<A0> > >))
                              (fusion_sequence_<State>)
                              ((target_< simd_< unspecified_<Data>,X > >))
                            )
  {
    typedef typename Data::type   result_type;

    template<class A0_> BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(A0_& a0, State const& state, Data const&) const
    {
      return nt2::splat<result_type>(boost::proto::value(a0));
    }
  };
} }

#endif
