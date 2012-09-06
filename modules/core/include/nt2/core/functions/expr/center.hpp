//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_CENTER_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_CENTER_HPP_INCLUDED

#include <nt2/core/functions/center.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/mean.hpp>
#include <nt2/include/functions/wmean.hpp> 
#include <nt2/include/functions/bsxfun.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::center_, tag::cpu_,
                              (A0),
                              (ast_<A0>) )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0),
      nt2::bsxfun(nt2::functor<tag::minus_>(), a0, nt2::mean(a0))
    )
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::center_, tag::cpu_,
                              (A0)(A1),
                              (ast_<A0>)
                              (scalar_<integer_<A1> > )
                              )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, const A1& a1),
      nt2::bsxfun(nt2::functor<tag::minus_>(), a0, nt2::mean(a0, a1))
    )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::center_, tag::cpu_,
                              (A0)(A1),
                              (ast_<A0>)(ast_<A1>) )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
      nt2::bsxfun(nt2::functor<tag::minus_>(), a0, nt2::wmean(a0, a1))
    )
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::center_, tag::cpu_,
                              (A0)(A1)(A2),
                              (ast_<A0>)(ast_<A1>)
                              (scalar_<integer_<A2> > )
                              )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, const A1& a1, const A2& a2),
      nt2::bsxfun(nt2::functor<tag::minus_>(), a0, nt2::wmean(a0, a1, a2))
    )
  };  
} }

#endif
