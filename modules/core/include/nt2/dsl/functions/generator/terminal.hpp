//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_GENERATOR_TERMINAL_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_GENERATOR_TERMINAL_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/core/utility/generative/category.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // generator terminal with a position in read mode
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(F)(State)(Data)
                            , ((ast_<generative_< unspecified_<A0>,F> >))
                              (fusion_sequence_<State>)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename boost::proto::result_of::value<A0>::type     gen;
    typedef typename  boost::dispatch::
                      meta::model_of<typename Data::type>::type   model_;
    typedef typename  boost::mpl::
                      apply < model_
                            , typename meta::strip<gen>::type::value_type
                            >::type                               result_type;

    template<class A0_> BOOST_FORCEINLINE result_type
    operator()(A0_& a0, State const& p, Data const& ) const
    {
      return boost::proto::value(a0)(p,meta::as_<result_type>());
    }
  };
} }

#endif
