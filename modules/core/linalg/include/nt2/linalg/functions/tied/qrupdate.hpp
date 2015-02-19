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
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/lartg.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/rot.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/norm2.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/core/utility/assign_swap.hpp>
#include <nt2/core/container/colon/colon.hpp>
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
       container::table<value_t> q = boost::proto::child_c<0>(a0);
       container::table<value_t> r = boost::proto::child_c<1>(a0);
       container::table<value_t> u = colvect(boost::proto::child_c<2>(a0));
       container::table<value_t> v = colvect(boost::proto::child_c<3>(a0));
       std::size_t m = height(q);
       std::size_t k = width(q);
       std::size_t n = width(r);
       bool full = k == m;
       rvalue_t ru = Zero<rvalue_t>();
       //c in the non-full case, we shall need the norm of u.
       if (!full){
         ru = norm2(u);
         NT2_DISPLAY(ru);
       }
       //form Q'*u. In the non-full case, form also u - Q*Q'u.
       container::table<value_t> w = mtimes(ctrans(q), u);
       std::cout << "1" << std::endl;
       if(!full) u -= mtimes(q, w);
//       NT2_DISPLAY(q);
       // generate rotations to eliminate Q'*u.
       container::table<rvalue_t> rw(of_size(n, 1));
       std::cout << "2" << std::endl;
       if(n) qrtv1(k, w, rw);
//        NT2_DISPLAY(w);
//        NT2_DISPLAY(rw);
       std::cout << "3" << std::endl;
       //apply rotations to R.
       if ((k > 1) && n) qrqh(k,n,r,rw(_(1, end_-1), 1),w(_(2, end_), 1));
//        NT2_DISPLAY(r);
       //apply rotations to Q.
       std::cout << "4" << std::endl;
       if (m && (k > 1)) qrot(m,k,q,rw(_(1, end_-1), 1),w(_(2, end_), 1),
                              boost::mpl::true_()); //backward
       std::cout << "apres qrot backward" << std::endl;
       NT2_DISPLAY(q);
       r(1, _)+= w(1)*rowvect(v); //update the first row of R.
       NT2_DISPLAY(r);
       //retriangularize R.
       qhqr(k,n,r,rw,w);
       std::cout << "apres retriangularize" << std::endl;
       NT2_DISPLAY(r);
       //apply rotations to Q.
       std::cout << "7" << std::endl;
       if (m && (k > 1) && (n!= 1)) qrot(m,min(k,n+1),q,rw(_(1, end_), 1),w(_(1, end_), 1)
                                        ,boost::mpl::false_());
       std::cout << "apres qrot forward" << std::endl;
       NT2_DISPLAY(q);
       std::cout << "8" << std::endl;
       NT2_DISPLAY(r);
       if (full)
       {
         boost::proto::child_c<0>(a1) = q;
         boost::proto::child_c<1>(a1) = r;
         std::cout << "9" << std::endl;
         return;
       }
       rvalue_t ruu =  norm2(u);
       if (false)//ruu < Eps<rvalue_t>()*ru)
       {
         boost::proto::child_c<0>(a1) = q;
         boost::proto::child_c<1>(a1) = r;
         std::cout << "10" << std::endl;
         return;
       }
       v *= ruu;
       u *= rec(ruu);
       ch1up(n, r, v, rw);
       std::cout << "11 apres ch1up" << std::endl;
       NT2_DISPLAY(r);
       reorth(n, k, q, u, rw, v);
       std::cout << "12 apres reorth" << std::endl;
       NT2_DISPLAY(q);
       boost::proto::child_c<0>(a1) = q;
       boost::proto::child_c<1>(a1) = r;
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
        lartg(u(i), rr, w(i), u(i+1), t);
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
      std::cout << "size(q)  "<< size(q)<< std::endl;
      std::cout << "size(u)  "<< size(u)<< std::endl;
      std::cout << "size(rw) "<< size(rw)<< std::endl;
      std::cout << "size(v)  "<< size(v) << std::endl;
      std::cout << "m        "<< m       << std::endl;
      std::cout << "k        "<< k       << std::endl;
      for(std::size_t i=1; i <= k; ++i)
      {
//         crot(m,Q(1,i),1,u,1,rw(i),conjg(v(i)))
//              n cx       cy  c     s

        for(std::size_t j=1; j <= m ; ++j)
        {
          value_t temp =  q(j, i)*rw(i)+conj(v(i))*v(j);
          u(j) = rw(i)*u(j)-v(i)*q(j, i);
          q(j, i) = temp;
         }
      }
    }
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class R,  class C, class S>
    BOOST_FORCEINLINE
    void qrqh(std::size_t m, std::size_t n, R& r, const C& c, const S& s) const
    {
      for(std::size_t i=1; i <= n; ++i)//apply stored rotations, column-wise
      {
        std::size_t ii = min(m-1,i);
        value_t t = r(ii+1,i);
        for(std::size_t j=ii; j >= 1u ; --j)
        {
          r(j+1,i) = c(j)*t - conj(s(j))*r(j,i);
          t = c(j)*r(j,i) + s(j)*t;
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
          value_t t = w(j)*r(j,i) + u(j)*ui;
          ui = w(j)*ui - conj(u(j))*r(j,i);
          r(j,i) = t;
        }
        // generate next rotation
        nt2::lartg(r(i,i),ui,w(i),u(i),rr);
        r(i,i) = rr;
      }
    }
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class Q,  class C, class S>
    BOOST_FORCEINLINE
    void qrot(std::size_t m, std::size_t n, Q& q
             , const C& c, const S& s, boost::mpl::true_ const &) const
    {
      auto cs =  conj(s);
      for(std::size_t i=n-1; i >= 1u; --i)//backward
      {
//        rot(m,q(1,i),1,q(1,i+1),1,c(i),conj(s(i)));
        auto ru = q(_(1, end_), i);
        auto rv = q(_(1, end_), i+1);
        container::table<value_t> temp = c(i)*ru + cs(i)*rv;
        rv = c(i)*rv- s(i)*ru;
        ru = temp;
      }
    }

    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class Q,  class C, class S>
    BOOST_FORCEINLINE
    void qrot(std::size_t m, std::size_t n, Q& q
             , const C& c, const S& s, boost::mpl::false_ const &) const
    {
      auto cs =  conj(s);
      for(std::size_t i=1; i < n; ++i)//forward
      {
        auto ru = q(_(1, end_), i);
        auto rv = q(_(1, end_), i+1);
//         NT2_DISPLAY(c(i));
//         NT2_DISPLAY(s(i));
//         NT2_DISPLAY(q(_(1, end_), i));
//         NT2_DISPLAY(q(_(1, end_), i+1));
        container::table<value_t> temp = c(i)*ru + cs(i)*rv;
        rv = c(i)*rv- s(i)*ru;
        ru = temp;
//         NT2_DISPLAY(ru);
//         NT2_DISPLAY(rv);
 //        rot(m,q(1,i),1,q(1,i+1),1,c(i),conj(s(i)));
      }
    }
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class R,  class C, class S>
    BOOST_FORCEINLINE
    void qhqr(std::size_t m, std::size_t n, R& r, C& c, S& s) const
    {
//       std::cout << " debut retriangularize m " << m << ", n " << n << std::endl;
//       NT2_DISPLAY(r);
      for(std::size_t i=1; i <= n; ++i)//apply stored rotations, column-wise
      {
//         std::cout << "i " << i << std::endl;
        value_t t = r(1, i);
        std::size_t ii = nt2::min(m,i);
        for(std::size_t j=1; j < ii ; ++j)
        {
//          std::cout << "i " << i << " j " << j << std::endl;
//           NT2_DISPLAY(r(j, i));
//           NT2_DISPLAY(c(j));
//           NT2_DISPLAY(t);
//           NT2_DISPLAY(s(j));
//           NT2_DISPLAY(r(j+1, i));
          r(j,i) = c(j)*t + s(j)*r(j+1,i);
          t = c(j)*r(j+1,i) - conj(s(j))*t;
//          NT2_DISPLAY(r(j, i));
//           NT2_DISPLAY(t);
        }
//         NT2_DISPLAY(r);
//         std::cout << "i " << i << " ii " << ii << " m " << m << " ii < m " << (ii < m) << std::endl;
        if (ii < m) //  generate next rotation
        {
//           std::cout << "icitte t " << t <<" r(ii+1,i) "<< r(ii+1,i)
//                     << " c(i) "<< c(i) <<" s(i) "<< s(i) <<" r(ii,i) "<< r(ii,i) << std::endl;
          nt2::lartg(t,r(ii+1,i), c(i),s(i),r(ii,i));
          r(ii+1, i) = Zero<value_t>();
//           std::cout << "latte  t " << t <<" r(ii+1,i) "<< r(ii+1,i)
//                     << " c(i "<< c(i) <<" s(i) "<< s(i) <<" r(ii,i) "<< r(ii,i) << std::endl;
        }
        else
        {
//           std::cout << "zutt1  t " << t <<" r(ii,i) "<< r(ii,i) << std::endl;
          r(ii, i) = t;
//           std::cout << "zutt2  t " << t <<" r(ii,i) "<< r(ii,i) << std::endl;
        }

//         std::cout << "after ii < m " << (ii < m) << std::endl;
//         NT2_DISPLAY(r);
//         NT2_DISPLAY(t);
      }
//       std::cout << " fin retriangularize" << std::endl;
//       NT2_DISPLAY(r);
    }
   };
} }

#endif

