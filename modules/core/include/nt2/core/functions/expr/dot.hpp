//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_DOT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_DOT_HPP_INCLUDED

#include <nt2/core/functions/dot.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/dot.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/conj.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dot_, tag::cpu_,
                              (A0)(A1),
                              (ast_<A0>)(ast_<A1>))
  {
    typedef typename meta::call<tag::conj_(A1 const&)>::type                    type1_t;
    typedef typename meta::call<tag::multiplies_(A0 const&, type1_t)>::type     type2_t; 
    typedef typename meta::call<tag::sum_(type2_t)>::type                   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return nt2::sum(nt2::multiplies(a0, conj(a1)));
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dot_, tag::cpu_,
                              (A0)(A1)(A2),
                              (ast_<A0>)(ast_<A1>)
                              (scalar_<integer_<A2> > )
                              )
  {
    typedef typename meta::call<tag::conj_(A1 const&) > ::type                       type1_t; 
    typedef typename meta::call<tag::multiplies_(A0 const&, type1_t) >::type         type2_t; 
    typedef typename meta::call<tag::sum_(type2_t, A2)>::type                    result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1, const A2& a2) const
    {
      return nt2::sum(nt2::multiplies(a0, conj(a1)), a2);
    }
  };
} }

#endif
