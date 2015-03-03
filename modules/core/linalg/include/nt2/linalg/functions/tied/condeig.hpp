//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_CONDEIG_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_CONDEIG_HPP_INCLUDED

#include <nt2/linalg/functions/condeig.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/norm2.hpp>
#include <nt2/include/functions/nseig.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/utility/assign_swap.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>

namespace nt2 {  namespace ext
{
  //============================================================================
  //condeig Scalar
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( condeig_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& ) const
    {
      return One<result_type>();
    }
  };
  //============================================================================
  // Capture a tie(l, u, p) = condeig(...) at assign time and resolve to optimized call
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( condeig_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::condeig_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
    typedef typename A0::value_type                                     value_t;
    typedef typename container::table<value_t>                          table_t;
    typedef typename meta::as_real<value_t>::type                      rvalue_t;
    typedef typename container::table<rvalue_t>                        rtable_t;
    typedef typename nt2::meta::as_complex<rvalue_t>::type             cvalue_t;
    typedef typename container::table<cvalue_t>                        ctable_t;
    typedef nt2::memory::container<tag::table_,  value_t, nt2::_2D>  o_semantic;
    typedef nt2::memory::container<tag::table_, rvalue_t, nt2::_2D>  r_semantic;
    typedef nt2::memory::container<tag::table_, cvalue_t, nt2::_2D>  c_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      table_t aa;
      NT2_AS_TERMINAL_INOUT(o_semantic, a, boost::proto::child_c<0>(a0), aa);
      gencond(a1, a, N1());
    }
  private:
    template < class A >  BOOST_FORCEINLINE
    void gencond(A1& a1, A & a, boost::mpl::long_<1>) const
    {
     NT2_AS_TERMINAL_OUT(r_semantic, s, boost::proto::child_c<0>(a1));
     ctable_t x, d, y;
     tie(x, d, y) = nseig(a);
     s = rec(nt2::abs(sum(conj(y)*x, 1)));
     assign_swap(boost::proto::child_c<0>(a1), s);
    }
    template < class A >  BOOST_FORCEINLINE
      void gencond(A1& a1, A & a, boost::mpl::long_<3>) const
    {
      NT2_AS_TERMINAL_OUT(c_semantic, x, boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT(c_semantic, d, boost::proto::child_c<1>(a1));
      NT2_AS_TERMINAL_OUT(r_semantic, s, boost::proto::child_c<2>(a1));
      ctable_t y;
      tie(x, d, y) = nseig(a);
      s = rec(nt2::abs(sum(conj(y)*x, 1)));
      assign_swap(boost::proto::child_c<0>(a1), x);
      assign_swap(boost::proto::child_c<1>(a1), d);
      assign_swap(boost::proto::child_c<2>(a1), s);
    }
    template < class A >  BOOST_FORCEINLINE
      void gencond(A1& a1, A & a, boost::mpl::long_<4>) const
    {
      NT2_AS_TERMINAL_OUT(c_semantic, x, boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT(c_semantic, d, boost::proto::child_c<1>(a1));
      NT2_AS_TERMINAL_OUT(c_semantic, y, boost::proto::child_c<2>(a1));
      NT2_AS_TERMINAL_OUT(r_semantic, s, boost::proto::child_c<3>(a1));
      tie(x, d, y) = nseig(a);
      s = rec(nt2::abs(sum(conj(y)*x, 1)));
      assign_swap(boost::proto::child_c<0>(a1), x);
      assign_swap(boost::proto::child_c<1>(a1), d);
      assign_swap(boost::proto::child_c<1>(a1), y);
      assign_swap(boost::proto::child_c<3>(a1), s);
    }

  };


} }

#endif
