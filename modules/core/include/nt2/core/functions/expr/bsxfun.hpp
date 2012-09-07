//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_BSXFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_BSXFUN_HPP_INCLUDED

#include <nt2/core/functions/bsxfun.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/container/dsl.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  /// Generates from a 2ary functor and 2 expressions
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::bsxfun_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              (ast_<A1>)
                              (ast_<A2>)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::bsxfun_
                                          , container::domain
                                          , A1 const&
                                          , A2 const&
                                          , box<A0>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2) const
    {
      return  boost::proto::
              make_expr<nt2::tag::bsxfun_, container::domain>
              ( boost::cref(a1)
              , boost::cref(a2)
              , boxify(a0)
              );
    }
  };

  /// INTERNAL ONLY
  /// Generates from a 2ary functor, an expression and a scalar
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::bsxfun_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              (ast_<A1>)
                              (scalar_< unspecified_<A2> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::bsxfun_
                                          , container::domain
                                          , A1 const&
                                          , A2
                                          , box<A0>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2) const
    {
      return  boost::proto::
              make_expr<nt2::tag::bsxfun_, container::domain>
              ( boost::cref(a1)
              , a2
              , boxify(a0)
              );
    }
  };

  /// INTERNAL ONLY
  /// Generates from a 2ary functor, a scalar and an expression
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::bsxfun_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              (scalar_< unspecified_<A1> >)
                              (ast_<A2>)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::bsxfun_
                                          , container::domain
                                          , A1
                                          , A2 const&
                                          , box<A0>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2) const
    {
      return  boost::proto::
              make_expr<nt2::tag::bsxfun_, container::domain>
              ( a1
              , boost::cref(a2)
              , boxify(a0)
              );
    }
  };
} }

#endif
