//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_NBTRUE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_NBTRUE_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/toolbox/reduction/functions/nbtrue.hpp>
#include <nt2/include/functions/sb2b.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/is_nez.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nbtrue_, tag::cpu_,
                              (A0),
                              (ast_<A0>) )
  {
    typedef typename meta::call <tag::is_nez_ ( A0 const&) >::type T1;
    typedef typename meta::call <tag::sb2b_   ( T1)        >::type T2;
    typedef typename meta::call <tag::sum_    ( T2)        >::type  result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return nt2::sum(nt2::sb2b(nt2::is_nez(a0)));
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nbtrue_, tag::cpu_,
                              (A0)(A1),
                              (ast_<A0>)
                              (scalar_<integer_<A1> > )
                              )
  {
    typedef typename meta::call <tag::is_nez_ ( A0 const&)     >::type T1;
    typedef typename meta::call <tag::sb2b_   ( T1)            >::type T2;
    typedef typename meta::call <tag::sum_    ( T2, A1 const &)>::type  result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1) const
    {
      return  nt2::sum(nt2::sb2b(nt2::is_nez(a0)), a1);
    }
  };
} }

#endif
