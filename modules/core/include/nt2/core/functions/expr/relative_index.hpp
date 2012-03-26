//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_RELATIVE_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_RELATIVE_INDEX_HPP_INCLUDED

#include <nt2/core/functions/relative_index.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/splat.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // When indexing an expression, return the evaluation of said expression
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_index_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (ast_<A0>)
                              (scalar_ < unspecified_<A1> >)
                              (target_< unspecified_<A2> >)
                            )
  {
    typedef typename A2::type result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0& indexer, const A1& pos, const A2&) const
    {
      return nt2::run ( indexer
                      , pos
                      , meta::as_<result_type>()
                      );
    }
  };

  //============================================================================
  // When indexing a scalar, evaluate as a scalar then splat
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_index_, tag::cpu_
                            , (A0)(Arity)(A1)(A2)
                            , ((expr_ < scalar_< unspecified_<A0> >
                                      , nt2::tag::terminal_
                                      , Arity
                                      >
                              ))
                              (scalar_ < unspecified_<A1> >)
                              (target_< unspecified_<A2> >)
                            )
  {
    typedef typename A0::value_type result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0& indexer, const A1& pos, const A2&) const
    {
      return nt2::run( indexer, pos, meta::as_<result_type>() );
    }
  };

  //============================================================================
  // When indexing on _, return the consecutive positions
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_index_, tag::cpu_
                            , (A0)(Arity)(A1)(A2)
                            , ((expr_ < colon_< A0 >
                                      , nt2::tag::terminal_
                                      , Arity
                                      >
                              ))
                              (scalar_ < unspecified_<A1> >)
                              (target_< unspecified_<A2> >)
                            )
  {
    typedef typename boost::dispatch::meta::
            scalar_of<typename A2::type>::type  result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0&, const A1& pos, const A2&) const
    {
      return pos;
    }
  };
} }

#endif
