//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_TIE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_TIE_HPP_INCLUDED

#include <nt2/core/functions/tie.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // run tie(...) does nothing (doesn't make sense to evaluate it)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(N0)
                            , ((node_<A0, nt2::tag::tie_, N0>))
                            )
  {
    typedef A0& result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0) const
    {
      return a0;
    }
  };

  //============================================================================
  // Call function for tie(...) = tieable_func(...)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(N0)(A1)(T1)(N1)
                            , ((node_<A0, nt2::tag::tie_, N0>))
                              ((node_<A1, tieable_<T1>, N1>))
                            )
  {
    typedef A0&                                         result_type;
    typedef typename boost::proto::tag_of<A1>::type     tag_t;
    typedef typename make_functor<tag_t,A0>::type       func_t;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      func_t callee;
      callee(a1, a0);

      return a0;
    }
  };

  //============================================================================
  // Handles elementwise  = tieable_func(...) by transforming it to
  //     tie(elementwise) = tieable_func(...)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::assign_, tag::cpu_
                              , (A0)(T0)(N0)(A1)(T1)(N1)
                              , (mpl::not_< is_same<T0, nt2::tag::tie_> >)
                              , ((node_ <A0, elementwise_<T0>, N0 > ))
                                ((node_ <A1, tieable_<T1>, N1>))
                              )
  {
    typedef typename meta::call<tag::tie_(A0&)>::type tied;
    typedef typename meta::call<tag::assign_(tied, A1&)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      return nt2::assign(nt2::tie(a0), a1);
    }
  };
} }

#endif
