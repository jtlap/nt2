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
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Handles tie(...) = tieable_func(...)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::assign_, tag::cpu_
                            , (A0)(N0)(A1)(T1)(N1)
                            , ((node_<A0, nt2::tag::tie_, N0>))
                              ((node_<A1, tieable_<T1>, N1>))
                            )
  {
    typedef A0&                                         result_type;
    typedef typename meta::strip<A1>::type              dest_t;
    typedef typename boost::proto::tag_of<dest_t>::type tag_t;
    typedef typename make_functor<tag_t,A0>::type       func_t;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      func_t callee;
      callee(a1, a0);

      return a0;
    }
  };

  //============================================================================
  // Handles terminal = tieable_func(...) by looking at it as a tie(terminal)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::assign_, tag::cpu_
                            , (A0)(T0)(A1)(T1)(N1)
                            , ((node_<A0, T0 , boost::mpl::long_<0> >))
                              ((node_<A1, tieable_<T1>, N1>))
                            )
  {
    typedef A0&                                         result_type;
    typedef typename meta::strip<A1>::type              dest_t;
    typedef typename boost::proto::tag_of<dest_t>::type tag_t;
    typedef typename make_functor<tag_t,A0>::type       func_t;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      func_t callee;
      callee( a1, nt2::tie(a0));

      return a0;
    }
  };

  //============================================================================
  // Handles elementwise = tieable_func(...) by looking at it as a tie(terminal)
  // over a local memory block.
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(T0)(N0)(A1)(T1)(N1)
                            , ((node_ <A0, elementwise_<T0>, N0 > ))
                              ((node_ <A1, tieable_<T1>, N1>))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::type      bound_t;
    typedef typename boost::remove_reference<bound_t>::type::value_type value_type;
    typedef A0& result_type;

    typedef typename meta::strip<A1>::type              dest_t;
    typedef typename boost::proto::tag_of<dest_t>::type tag_t;
    typedef typename make_functor<tag_t,A0>::type       func_t;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      nt2::container::table<value_type> bound = boost::proto::child_c<0>(a1);

      func_t callee;
      callee( a1, nt2::tie(bound) );

      a0 = bound;
      return a0;
    }
  };
} }

#endif
