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

#include <nt2/dsl/functions/terminal.hpp>
#include <boost/fusion/include/size.hpp>

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
    typedef typename boost::dispatch::meta::
    semantic_of<A0>::type                                  result_type;
    
    template<class A0_>
    result_type operator()(A0_& a0, _0D const&, Data const&) const
    {
       return boost::proto::value(a0);
    }
  };
    
  // table terminal with a position
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(S0)(State)(Data)
                            , ((ast_<table_< unspecified_<A0>, S0 > >))
                              (fusion_sequence_<State>)
                              (unspecified_<Data>)
                            )
  {
    typedef typename boost::dispatch::meta::
    scalar_of< typename boost::dispatch::meta::
               semantic_of<A0>::type
             >::type                                       result_type;
    
    template<class A0_>
    result_type operator()(A0_& a0, State const& state, Data const&) const
    {
       typedef typename boost::proto::result_of::value<A0_>::value_type value_type;
       typedef typename value_type::extent_type extent_type;
       return boost::proto::value(a0)(extent_type(state));
    }
  };

  // scalar terminal, always value
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((ast_<scalar_< unspecified_<A0> > >))
                              (fusion_sequence_<State>)
                              (unspecified_<Data>)
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
} }

#endif
