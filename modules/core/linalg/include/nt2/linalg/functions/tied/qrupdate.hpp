//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_QRUPDATE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_QRUPDATE_HPP_INCLUDED

#include <nt2/linalg/functions/qrupdate.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/ctranspose.hpp>
//#include <nt2/include/functions/lartg.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/rot.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/planerot.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/fms.hpp>
#include <nt2/include/functions/dec.hpp>
#include <nt2/include/functions/inc.hpp>
#include <nt2/include/functions/norm2.hpp>
#include <nt2/include/functions/sincos.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/halfeps.hpp>
#include <nt2/core/utility/assign_swap.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/utility/assign_swap.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <boost/assert.hpp>
#include <nt2/table.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Capture a tie(q1, r1) = qrupdate(q, r, u, v) at assign time
  // and resolve to optimized call
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( qrupdate_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::qrupdate_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
    typedef typename A0::value_type                                     value_t;
    typedef typename meta::as_real<value_t>::type                      rvalue_t;
    typedef nt2::memory::container<tag::table_,  value_t, nt2::_2D>  o_semantic;
    typedef nt2::memory::container<tag::table_, rvalue_t, nt2::_2D>  r_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      update(a0, a1, N0(), N1());
    }

  private:
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    BOOST_FORCEINLINE
      void update(A0& a0, A1 & a1
                  , boost::mpl::long_<4> const&
                  , boost::mpl::long_<2> const&) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, q, boost::proto::child_c<0>(a0), boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_INOUT(o_semantic, r, boost::proto::child_c<1>(a0), boost::proto::child_c<1>(a1));
      if (isempty(q)) finalize(a1, q, r);
      container::table<value_t> u = colvect(boost::proto::child_c<2>(a0));
      container::table<value_t> v = colvect(boost::proto::child_c<3>(a0));
      std::size_t m = height(q);
      std::size_t k = width(q);
      std::size_t n = width(r);
      bool full = k == m;
//       std::cout << "size(q)  "<< size(q)<< std::endl;
//       std::cout << "size(r)  "<< size(r)<< std::endl;
//       std::cout << "size(u)  "<< size(u)<< std::endl;
//       std::cout << "size(v)  "<< size(v) << std::endl;
//       std::cout << "m        "<< m       << std::endl;
//       std::cout << "k        "<< k       << std::endl;
//       std::cout << "n        "<< n       << std::endl;
      BOOST_ASSERT_MSG(full || ((k!= m) && (n <= m)), "improper q and r sizes");
      BOOST_ASSERT_MSG(numel(u) == m, "wrong u length");
      BOOST_ASSERT_MSG(numel(v) == n, "wrong v length");
      rvalue_t ru = Zero<rvalue_t>();
      //c in the non-full case, we shall need the norm of u.
      if (!full) ru = norm2(u);
      //form Q'*u. In the non-full case, form also u - Q*Q'u.
      container::table<value_t> w = mtimes(ctrans(q), u);
      if(!full) u -= mtimes(q, w);
      // generate rotations to eliminate Q'*u.
      container::table<rvalue_t> rw(of_size(n, 1));
      qrtv1(k, w, rw);
      if (k > 1)
      {
        //apply rotations to R.
        qrqh(k,n,r,rw(_(1, end_-1), 1),w(_(2, end_), 1));
        //apply rotations to Q backward.
        qrot(k,q,rw(_(1, end_-1), 1),w(_(2, end_), 1), boost::mpl::true_());
      }
      r(1, _)+= w(1)*rowvect(v); //update the first row of R.
      //retriangularize R.
      qhqr(k,n,r,rw,w);
      //apply rotations to Q forward.
      if ((k > 1) && (n!= 1))
        qrot(min(k,n+1),q,rw(_(1, end_), 1),w(_(1, end_), 1),boost::mpl::false_());
      if (full)
      {
        finalize(a1, q, r);
        return;
      }
      rvalue_t ruu =  norm2(u);
      if (ruu < Halfeps<rvalue_t>()*ru)
      {
        finalize(a1, q, r);
        return;
      }
      v *= ruu;
      u *= rec(ruu);
      ch1up(n, r, v, rw);
      reorth(n, k, q, u, rw, v);
      finalize(a1, q, r);
    }

    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class Q,  class R>
      BOOST_FORCEINLINE
      void finalize(A1& a1, Q& q, R& r) const
    {
      assign_swap(boost::proto::child_c<0>(a1), q);
      assign_swap(boost::proto::child_c<1>(a1), r);
    }

    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class U,  class W>
      BOOST_FORCEINLINE
      void qrtv1(size_t n, U& u,  W& w) const
    {
      value_t rr = u(n), t;
      for(std::size_t i=n-1; i >= 1 ; --i)
      {
        tie(u(i+1), w(i), t) = planerot(cons(of_size(2, 1), u(i), rr), nt2::tag::sincos_());
//        lartg(u(i), rr, w(i), u(i+1), t);
        rr = t;
      }
      u(1) = rr;
    }
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
//  reorth(m, n, q, u, rw, v);
    template < class Q,  class U, class RW, class V>
    BOOST_FORCEINLINE
    void reorth(std::size_t m, std::size_t k, Q& q,  U& u, RW& rw,  V& v) const
    {
      for(std::size_t i=1; i <= k; ++i)
      {
        auto j = _(1u, m);
        container::table<value_t> temp = fma(q(j, i), rw(i), conj(v(i))*v(j));
        u(j) = fms(rw(i), u(j), v(i)*q(j, i));
        q(j, i) = temp;
      }

    }
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class R,  class C, class S>
    BOOST_FORCEINLINE
    void qrqh(std::size_t m, std::size_t n, R& r, const C& c, const S& s) const
    {
      for(std::size_t i=1; i <= n; ++i)
      {
        std::size_t ii = min(m-1,i);
        value_t t = r(ii+1,i);
        for(std::size_t j=ii; j >= 1u ; --j)
        {
          r(j+1,i) = fms(c(j), t, conj(s(j))*r(j,i));
          t = fma(c(j), r(j,i), s(j)*t);
        }
        r(1,i) = t;
      }
    }
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class R,  class U, class W>
    BOOST_FORCEINLINE
    void ch1up(std::size_t n, R& r, U& u, W& w) const
    {
      for(std::size_t i=1; i <= n; ++i)//apply stored rotations, column-wise
      {
        value_t rr;
        value_t ui = conj(u(i));
        for(std::size_t j=1; j < i; ++j)
        {
          value_t t = fma(w(j), r(j,i), u(j)*ui);
          ui = fms(w(j), ui, conj(u(j))*r(j,i));
          r(j,i) = t;
        }
        // generate next rotation
        tie(u(i), w(i), rr) = planerot(cons(of_size(2, 1), r(i,i),ui), nt2::tag::sincos_());
//        nt2::lartg(r(i,i),ui,w(i),u(i),rr);
        r(i,i) = rr;
      }
    }
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class Q,  class C, class S>
    BOOST_FORCEINLINE
    void qrot(std::size_t n, Q& q
             , const C& c, const S& s, boost::mpl::true_ const &) const
    {
      auto cs =  conj(s);
      for(std::size_t i=n-1; i >= 1u; --i)//backward
      {
        auto ru = q(_(1, end_), i);
        auto rv = q(_(1, end_), i+1);
        container::table<value_t> temp = fma(c(i), ru, cs(i)*rv);
        rv = fms(c(i), rv, s(i)*ru);
        ru = temp;
      }
    }

    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class Q,  class C, class S>
    BOOST_FORCEINLINE
    void qrot(std::size_t n, Q& q
             , const C& c, const S& s, boost::mpl::false_ const &) const
    {
      auto cs =  conj(s);
      for(std::size_t i=1; i < n; ++i)//forward
      {
        auto ru = q(_(1, end_), i);
        auto rv = q(_(1, end_), i+1);
        container::table<value_t> temp = fma(c(i), ru, cs(i)*rv);
        rv = fms(c(i), rv, s(i)*ru);
        ru = temp;
      }
    }
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class R,  class C, class S>
    BOOST_FORCEINLINE
    void qhqr(std::size_t m, std::size_t n, R& r, C& c, S& s) const
    {
      for(std::size_t i=1; i <= n; ++i)//apply stored rotations, column-wise
      {
        value_t t = r(1, i);
        const std::size_t ii = nt2::min(m,i);
        for(std::size_t j=1; j < ii ; ++j)
        {
          r(j,i) = fma(c(j), t, s(j)*r(j+1,i));
          t = fms(c(j), r(j+1,i), conj(s(j))*t);
        }
        if (ii < m) //  generate next rotation
        {
          tie(s(i), c(i), r(ii,i)) = planerot(cons(of_size(2, 1), t,r(ii+1,i)), nt2::tag::sincos_());
//        nt2::lartg(t,r(ii+1,i), c(i),s(i),r(ii,i));
          r(ii+1, i) = Zero<value_t>();
        }
        else
        {
          r(ii, i) = t;
        }
      }
    }
  };
} }

#endif

