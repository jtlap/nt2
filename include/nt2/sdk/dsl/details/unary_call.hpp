/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_DETAILS_UNARY_CALL_HPP_INCLUDED
#define NT2_SDK_DSL_DETAILS_UNARY_CALL_HPP_INCLUDED

#include <nt2/sdk/dsl/category.hpp>

////////////////////////////////////////////////////////////////////////////////
// This file generate basic EDSL expression wrapper over any nt2 function
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Unary node
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( Func , tag::cpu_
                      , (Func)(D)
                        (A0)(T0)(S0)
                      , ((expr_<A0, domain_<D>, T0, S0>))
                      )

namespace nt2 { namespace ext
{
  template< class Func, class D, class T0, class S0 , class Dummy >
  struct  call< Func(tag::expr_<D,T0,S0>)
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;

    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename boost::proto::result_of::
      make_expr < Func
                , typename meta::strip<A0>::type const&
                >::type type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      return boost::proto::make_expr<Func>(boost::cref(a0));
    }
  };
} }

#endif
