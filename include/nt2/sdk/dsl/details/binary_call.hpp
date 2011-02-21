/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_DETAILS_BINARY_CALL_HPP_INCLUDED
#define NT2_SDK_DSL_DETAILS_BINARY_CALL_HPP_INCLUDED

#include <nt2/sdk/dsl/category.hpp>

////////////////////////////////////////////////////////////////////////////////
// This file generate basic EDSL expression wrapper over any nt2 function
////////////////////////////////////////////////////////////////////////////////

namespace nt2 { namespace details
{
  template<class Func>
  struct make_binary : ext::callable
  {
    template<class Sig> struct result;

    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
    {
      typedef typename boost::proto::result_of::
      make_expr < Func
                , typename meta::strip<A0>::type const&
                , typename meta::strip<A1>::type const&
                >::type type;
    };

    template<class A0,class A1> inline
    typename result<make_binary(A0 const&, A1 const&)>::type
    operator()(A0 const& a0, A1 const& a1) const
    {
      return boost::proto::make_expr<Func>(boost::cref(a0),boost::cref(a1));
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Binary node expr/expr
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( Func , tag::cpu_
                      , (Func)(D)
                        (A0)(T0)(S0)
                        (A1)(T1)(S1)
                      , ((expr_<A0, domain_<D>, T0, S0>))
                        ((expr_<A1, domain_<D>, T1, S1>))
                      )

namespace nt2 { namespace ext
{
  template<class Func, class D, class T0, class S0, class T1, class S1, class X>
  struct  call< Func(tag::expr_<D,T0,S0>,tag::expr_<D,T1,S1>), tag::cpu_, X>
        : details::make_binary<Func> {};
} }

////////////////////////////////////////////////////////////////////////////////
// Binary node expr/other
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( Func , tag::cpu_
                      , (Func)(D)
                        (A0)(T0)(S0)
                        (A1)
                      , ((expr_<A0, domain_<D>, T0, S0>))
                        (unspecified_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Func, class D, class T0, class S0, class X>
  struct  call< Func(tag::expr_<D,T0,S0>,tag::unspecified_), tag::cpu_, X>
        : details::make_binary<Func> {};
} }

////////////////////////////////////////////////////////////////////////////////
// Binary node other/expr
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( Func , tag::cpu_
                      , (Func)(D)
                        (A0)
                        (A1)(T1)(S1)
                      , (unspecified_<A0>)
                        ((expr_<A1, domain_<D>, T1, S1>))
                      )

namespace nt2 { namespace ext
{
  template<class Func, class D, class T1, class S1, class X>
  struct  call< Func(tag::unspecified_,tag::expr_<D,T1,S1>), tag::cpu_, X>
        : details::make_binary<Func> {};
} }

#endif
