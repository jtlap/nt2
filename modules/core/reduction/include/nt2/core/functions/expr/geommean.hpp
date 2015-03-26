//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_GEOMMEAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_GEOMMEAN_HPP_INCLUDED

#include <nt2/core/functions/geommean.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/geommean.hpp>
#include <nt2/include/functions/prod.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/size.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( geommean_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>)) )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::call < nt2::tag::prod_(A0 const&)>::type T1;
    typedef typename meta::call < nt2::tag::pow_(T1, value_type)>::type result_type;


    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      value_type f = rec(value_type(nt2::size(a0, nt2::firstnonsingleton(a0))));
      return nt2::pow(nt2::prod(a0), f);
    }
  };
  BOOST_DISPATCH_IMPLEMENT  ( geommean_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> > )
                              )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::call < nt2::tag::prod_(A0 const&, A1 const &)>::type T1;
    typedef typename meta::call < nt2::tag::pow_(T1, value_type)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1) const
    {
      value_type f = rec(value_type(nt2::size(a0, a1)));
      return nt2::pow(nt2::prod(a0, a1), f);
    }
  };
} }

#endif
