//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTIONS_CONTAINER_INBTRUE_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTIONS_CONTAINER_INBTRUE_HPP_INCLUDED

#include <nt2/toolbox/reduction/functions/inbtrue.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/sb2b.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/core/container/dsl.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::inbtrue_, tag::cpu_,
                              (A0),
                              (ast_<A0>)
                            )
  {
    typedef typename meta::call <tag::sb2b_  (A0) >::type T1;
    typedef typename meta::call <tag::toint_ (T1)        >::type T2;
    typedef typename meta::call <tag::sum_   (T2)        >::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return nt2::sum(nt2::toint(nt2::sb2b(a0)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::inbtrue_, tag::cpu_,
                              (A0)(A1),
                              (ast_<A0>)
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef typename meta::call <tag::sb2b_  (A0)     >::type T1;
    typedef typename meta::call <tag::toint_ (T1)            >::type T2;
    typedef typename meta::call <tag::sum_   (T2, A1) >::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1) const
    {
      return  nt2::sum(nt2::toint(nt2::sb2b(a0)), a1);
    }
  };
} }

#endif
