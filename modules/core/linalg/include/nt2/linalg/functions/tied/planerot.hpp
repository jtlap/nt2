//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_PLANEROT_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_PLANEROT_HPP_INCLUDED

#include <nt2/linalg/functions/planerot.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/hypot.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/isrow.hpp>
#include <nt2/include/functions/negif.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqr_abs.hpp>
#include <nt2/include/functions/swap.hpp>

#include <nt2/include/functions/tie.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <nt2/sdk/meta/is_scalar.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // This version of planerot is called whenever a tie(...) = planerot(...) is captured
  // before assign is resolved. As a tieable function, planerot retrieves rhs/lhs
  // pair as inputs
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( planerot_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::planerot_, N0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
    typedef typename meta::strip<child0>::type                          dest0_t;
    typedef typename dest0_t::value_type                                value_t;
    typedef typename nt2::meta::as_real<value_t>::type                 rvalue_t;
    typedef nt2::container::table<value_t>                                tab_t;
    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      value_t s, r;
      rvalue_t c;
      compute_scr(a0, s, c, r, typename nt2::meta::is_complex<value_t>::type());
      results(r, s, c, a0, a1, N1(), N0());
    }

  private:
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    BOOST_FORCEINLINE
    void preparexs(value_t& x, value_t& s, A0 & a0
                  , boost::mpl::false_ const&// first input is a vector not a scalar
                  ) const
    {
      x = boost::proto::child_c<0>(a0)(1);
      s = boost::proto::child_c<0>(a0)(2);
    }

    BOOST_FORCEINLINE
    void preparexs(value_t& x, value_t& s, A0 & a0
                  , boost::mpl::true_ const& // first input is a scalar
                  ) const
    {
      x = boost::proto::child_c<0>(a0);
      s = boost::proto::child_c<1>(a0);
    }

    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    BOOST_FORCEINLINE
      void compute_scr(A0 & a0, value_t& s, rvalue_t& c, value_t& r, const boost::mpl::true_ & ) const
    {
      value_t x;
      preparexs(x, s, a0, typename nt2::meta::is_scalar<dest0_t>::type());
      if(is_eqz(s))
      {
        r = x;
        c =  One<rvalue_t>();
        return;
      }
      if(is_eqz(x))
      {
        c = Zero<rvalue_t>();
        s = s/sqr_abs(s);
        r = One<value_t>();
        return;
      }
      rvalue_t h = nt2::hypot(x, s);
      rvalue_t rh = rec(h);
      value_t ic = x*rh;
      s *= rh;
      s *= conj(ic);
      r = h*ic;
      ic *= conj(ic);
      c = real(ic);
      rvalue_t rn = rec(hypot(c, s));
      c*= rn;
      s*= rn;
      r*= rn;
    }
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    BOOST_FORCEINLINE
    void compute_scr(A0 & a0, value_t& s, rvalue_t& c, value_t& r
                    , const boost::mpl::false_ & ) const
    {
      preparexs(c, s, a0, typename nt2::meta::is_scalar<dest0_t>::type());
//       c = boost::proto::child_c<0>(a0)(1);
//       s = boost::proto::child_c<0>(a0)(2);
      r = nt2::hypot(c, s);
      if (s)
      {
        value_t rr = rec(r);
        c *= rr;
        s *= rr;
      }
      else
      {
        c =  One<value_t>();
        s =  Zero<value_t>();
      }
    }
    //==========================================================================
    // INTERNAL ONLY
    // compute rotation matrix
    //==========================================================================
    BOOST_FORCEINLINE
    void results(const value_t, const value_t s, const rvalue_t c
                , A0 & a0, A1 & a1
                , boost::mpl::long_<1> const&, boost::mpl::long_<1> const&) const
    {
//      NT2_DISPLAY(c);
//      NT2_DISPLAY(s);
      child0& rot(boost::proto::child_c<0>(a1));
      rot.resize(of_size(2, 2));
      rot(1, 1) = c;
      rot(2, 2) = c;
      rot(1, 2) = conj(s);
      rot(2, 1) = -s;
      if (isrow(boost::proto::child_c<0>(a0))) nt2::swap(rot(1, 2), rot(2, 1));
    }

    //==========================================================================
    // INTERNAL ONLY
    // fills the second arg out
    //==========================================================================
    BOOST_FORCEINLINE
    void results(const value_t r, const value_t s, const rvalue_t c, A0 & a0, A1 & a1
                , boost::mpl::long_<2> const&, boost::mpl::long_<1> const&) const
    {
      results(r, s, c, a0, a1, boost::mpl::long_<1>(), boost::mpl::long_<1>());
      container::table<value_t, of_size_<2, 1>> y;
      y(1) = r; y(2) = nt2::Zero<value_t>();
      boost::proto::child_c<1>(a1) = y;
    }

    //==========================================================================
    // INTERNAL ONLY
    // returns sine and cosine
    //==========================================================================
    BOOST_FORCEINLINE
    void results(const value_t, const value_t s, const rvalue_t c, A0 &, A1 & a1
                , boost::mpl::long_<2> const&, boost::mpl::long_<2> const&) const
    {
      boost::proto::child_c<0>(a1) = conj(s);
      boost::proto::child_c<1>(a1) = c;
    }

    //==========================================================================
    // INTERNAL ONLY
    // returns sine and cosine and transformed y(1)
    //==========================================================================
    BOOST_FORCEINLINE
    void results(const value_t r, const value_t s, const rvalue_t c, A0 &, A1 & a1, boost::mpl::long_<3> const&, boost::mpl::long_<2> const&) const
    {
      boost::proto::child_c<0>(a1) = conj(s);
      boost::proto::child_c<1>(a1) = c;
      boost::proto::child_c<2>(a1) = r;
    }
//     //==========================================================================
//     // INTERNAL ONLY
//     // returns sine and cosine
//     //==========================================================================
//     BOOST_FORCEINLINE
//     void results(const value_t, const value_t s, const rvalue_t c, A0 &, A1 & a1, boost::mpl::long_<2> const&, boost::mpl::long_<3> const&) const
//     {
//       boost::proto::child_c<0>(a1) = s;
//       boost::proto::child_c<1>(a1) = c;
//     }

//     //==========================================================================
//     // INTERNAL ONLY
//     // returns sine and cosine and transformed y(1)
//     //==========================================================================
//     BOOST_FORCEINLINE
//     void results(const value_t r, const value_t s, const rvalue_t c, A0 &, A1 & a1, boost::mpl::long_<3> const&, boost::mpl::long_<3> const&) const
//     {
//       boost::proto::child_c<0>(a1) = s;
//       boost::proto::child_c<1>(a1) = c;
//       boost::proto::child_c<2>(a1) = r;
//     }
  };
} }

#endif
