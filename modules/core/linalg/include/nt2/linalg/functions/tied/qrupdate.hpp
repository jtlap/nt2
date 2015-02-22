//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_QRUPDATE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_QRUPDATE_HPP_INCLUDED

#include <nt2/linalg/functions/qrupdate.hpp>
#include <nt2/linalg/details/qr/qr_kernel.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/fms.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/norm2.hpp>
#include <nt2/include/functions/planerot.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/constants/halfeps.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/core/container/extremum/extremum.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <boost/assert.hpp>

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
      if (isempty(q)) details::qr_kernel<value_t>::finalize(a1, q, r);
      container::table<value_t> u = colvect(boost::proto::child_c<2>(a0));
      container::table<value_t> v = colvect(boost::proto::child_c<3>(a0));
      std::size_t m = height(q);
      std::size_t k = width(q);
      std::size_t n = width(r);
      bool square = issquare(q);
      BOOST_ASSERT_MSG(square || ((k!= m) && (n <= m)), "improper q and r sizes");
      BOOST_ASSERT_MSG(numel(u) == m, "wrong u length");
      BOOST_ASSERT_MSG(numel(v) == n, "wrong v length");
      rvalue_t ru = Zero<rvalue_t>();
      if (!square) ru = norm2(u);
      container::table<value_t> tmp = mtimes(ctrans(q), u);
      if(!square) u -= mtimes(q, tmp);
      // generate rotations to eliminate ctrans(q)*u.
      container::table<rvalue_t> rtmp(of_size(k, 1));
      details::qr_kernel<value_t>::mkzeroingrots(k, tmp, rtmp);
      if (k > 1)
      {
        details::qr_kernel<value_t>::mkhessenberg(k,n,r,rtmp(_(1, end_-1), 1),tmp(_(2, end_), 1));
        details::qr_kernel<value_t>::rotate_backward(k,q,rtmp(_(1, end_-1), 1),tmp(_(2, end_), 1));
      }
      r(1, _)+= tmp(1)*rowvect(v); //update the first row of R.
      details::qr_kernel<value_t>::retriangularize(k,n,r,rtmp,tmp);
      if ((k > 1) && (n!= 1))
        details::qr_kernel<value_t>::rotate_forward(min(k,n+1),q,rtmp,tmp);
      if (square)
      {
        details::qr_kernel<value_t>::finalize(a1, q, r);
        return;
      }
      rvalue_t ruu =  norm2(u);
      if (ruu < Halfeps<rvalue_t>()*ru)
      {
        details::qr_kernel<value_t>::finalize(a1, q, r);
        return;
      }
      v *= ruu;
      u *= rec(ruu);
      updatetriangular(n, r, v, rtmp);
      reorthogonalize(n, k, q, u, rtmp, v);
      details::qr_kernel<value_t>::finalize(a1, q, r);
    }

    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class Q,  class U, class RTMP, class V>
    BOOST_FORCEINLINE
    void reorthogonalize(std::size_t m, std::size_t k, Q& q,  U& u, RTMP& rtmp,  V& v) const
    {
      auto j = _(1, m);
      for(std::size_t i=1; i <= k; ++i)
      {
        container::table<value_t> temp = fma(q(j, i), rtmp(i), conj(v(i))*v(j));
        u(j) = fms(rtmp(i), u(j), v(i)*q(j, i));
        q(j, i) = temp;
      }

    }

    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class R,  class U, class TMP>
    BOOST_FORCEINLINE
    void updatetriangular(std::size_t n, R& r, U& u, TMP& tmp) const
    {
      for(std::size_t i=1; i <= n; ++i)
      {
        value_t rr;
        value_t ui = conj(u(i));
        for(std::size_t j=1; j < i; ++j)
        {
          value_t t = fma(tmp(j), r(j,i), u(j)*ui);
          ui = fms(tmp(j), ui, conj(u(j))*r(j,i));
          r(j,i) = t;
        }
        tie(u(i), tmp(i), rr) = planerot(cons(of_size(2, 1), r(i,i),ui), nt2::tag::sincos_());
        r(i,i) = rr;
      }
    }
  };
} }

#endif

