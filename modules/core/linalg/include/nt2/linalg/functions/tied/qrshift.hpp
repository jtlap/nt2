//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_QRSHIFT_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_QRSHIFT_HPP_INCLUDED

#include <nt2/linalg/functions/qrshift.hpp>
#include <nt2/linalg/details/qr/qr_kernel.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/inc.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Capture a tie(q1, r1) = qrshift(q, r, i, j) at assign time
  // and resolve to optimized call
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( qrshift_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::qrshift_, N0, nt2::container::domain>))
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
      shift(a0, a1, N0(), N1());
    }

  private:
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    static BOOST_FORCEINLINE
    void shift(A0& a0, A1 & a1
                  , boost::mpl::long_<4> const&
                  , boost::mpl::long_<2> const&)
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, q, boost::proto::child_c<0>(a0), boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_INOUT(o_semantic, r, boost::proto::child_c<1>(a0), boost::proto::child_c<1>(a1));
      if (isempty(q)) details::qr_kernel<value_t>::finalize(a1, q, r);
      const std::size_t i = boost::proto::child_c<2>(a0);
      const std::size_t j = boost::proto::child_c<3>(a0);
      const std::size_t m = height(q);
      const std::size_t k = width(q);
      const std::size_t n = width(r);
      container::table<rvalue_t> rtmp(of_size(k, 1));
      container::table< value_t>  tmp(of_size(k, 1));
      BOOST_ASSERT_MSG(((k == m) || (k != n && n > m)), "improper q and r sizes for qrshift");
      container::table< value_t, _2D> r0; //will contain shifted r
      if (i < j)
      {
        // shift matrix r
        r0 = horzcat(horzcat(horzcat(r(_, _(1, i-1))
                                    , r(_, _(i+1, j)))
                            , r(_, i))
                    , r(_, _(j+1, nt2::end_))
                    );
        if (i < k)
        {
          const std::size_t kk =  nt2::min(k,j);
          auto ii = _(i, k);
          const std::size_t l1 = inc(kk)-i;
          auto  rr = r0(ii, _(i, n));
          details::qr_kernel<value_t>::retriangularize(l1,inc(n)-i,rr,rtmp,tmp);
          auto qqi = q(_, ii);
          details::qr_kernel<value_t>::rotate_forward(l1,qqi,rtmp,tmp);
        }
        details::qr_kernel<value_t>::finalize(a1, q, r0);
        return;
      }
      else if (j < i)
      {
        // shift matrix r
        r0 = horzcat(horzcat(horzcat(r(_, _(1, j-1))
                                    , r(_, i))
                            , r(_, _(j, i-1)))
                    , r(_, _(i+1, nt2::end_))
                    );
        if (j < k)
        {
          std::size_t jj = nt2::min(inc(j),n);
          std::size_t kk = nt2::min(k,i);
          std::size_t l1 = kk+1-j;
          auto jji = _(j, n);
          auto rr = r0(jji,j);
          details::qr_kernel<value_t>::mkzeroingrots(l1,rr,rtmp);
          auto rr1 = r0(jji, _(jj, n));
          auto rr2 = r0(inc(jji), jji);
          details::qr_kernel<value_t>::mkhessenberg(l1,n-j,rr1,rtmp,rr2);
          // apply rotations to Q
          auto qqj = q(_, jji);
          details::qr_kernel<value_t>::rotate_backward(l1,qqj,rtmp,rr2);
          // update r0 jth column.
          r0(_(j+1, kk), j) = Zero<value_t>();
        }
        details::qr_kernel<value_t>::finalize(a1, q, r0);
        return;
      }
      details::qr_kernel<value_t>::finalize(a1, q, r);
    }
  };
} }

#endif

