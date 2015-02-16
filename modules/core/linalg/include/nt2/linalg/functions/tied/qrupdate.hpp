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
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/globalany.hpp>
#include <nt2/include/functions/hypot.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/realsqrt.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/core/utility/assign_swap.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Capture a tie(l, u, p) = qrupdate(...) at assign time and resolve to optimized call
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

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      update(a0, a1, N0(), N1());
    }

  private:
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
     BOOST_FORCEINLINE
     container::table<value_t> computereflectors(const value_t x, const value_t y)
     {
       return planerot(cons<value_t>(of_size<2, 1>(), x, y));
     }
     BOOST_FORCEINLINE
     container::table<value_t> applyreflectors(const value_t x, const value_t y)
     {

     }
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
       value_t rho = Zero<value_t>(); //, c, s;
       container::table<value_t> t(of_size(1, size(q, 2)));
       orthogonalize(q, v, t, rho);
       container::table<value_t> g(of_size(2, 2)) = computereflectors(t(n), rho);
//       computereflectors(t(n), rho, c, s);
       applyreflector(c, s, n, n, r(n, n), rho)
       applyreflector(c, s, 1, m, q(n, n), v(n))
    }

//     //==========================================================================
//     // INTERNAL ONLY
//     //==========================================================================
//     BOOST_FORCEINLINE
//       void compute(A0& a0, A1 & a1
//                   , boost::mpl::long_<2> const&
//                   , boost::mpl::long_<1> const&) const
//     {
//       update(a0, a1, N1(), nt2::tag::plus_());
//     }

//     //==========================================================================
//     // INTERNAL ONLY
//     //==========================================================================
//     BOOST_FORCEINLINE
//     void compute(A0& a0, A1 & a1
//                , boost::mpl::long_<3> const&
//                , boost::mpl::long_<2> const&) const
//     {
//       typedef typename boost::proto::result_of::child_c<A0&,2>::value_type       choice_t;
//       typedef typename choice_t::value_type                                           c_t;
//       boost::proto::child_c<1>(a1) = update(a0, a1, N1(), c_t());
//     }

//     //==========================================================================
//     // INTERNAL ONLY
//     //==========================================================================
//     BOOST_FORCEINLINE
//     void compute(A0& a0, A1 & a1
//                , boost::mpl::long_<2> const&
//                , boost::mpl::long_<2> const&) const
//     {
//       boost::proto::child_c<1>(a1) = update(a0, a1, N1(), nt2::tag::plus_());
//     }
//     //==========================================================================
//     // INTERNAL ONLY
//     //==========================================================================
//     BOOST_FORCEINLINE
//     std::size_t update(A0& a0, A1 & a1
//                  , N1 const &
//                  , nt2::tag::plus_ const &  ) const
//     {
//       container::table<value_t> l1 = boost::proto::child_c<0>(a0);
//       container::table<value_t> x  = rowvect(boost::proto::child_c<1>(a0));
//       std::size_t p = length(x);
//       if (globalany(is_lez(diag_of(l1))))
//       {
//         boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
//         error(2, N1());
//         return 2;
//       }
//       for(std::size_t k = 1; k <= p; ++k)
//       {
//         value_t ll = l1(k, k);
//         if(ll <= 0)
//         {
//           boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
//           error(2, N1());
//           return 2;
//         }
//         value_t r =  hypot(ll, x(k));
//         value_t c =  r/ll;
//         value_t rc =  rec(c);
//         value_t s = x(k)/ll;
//         l1(k, k) = r;
//         auto kp1p = _(k+1, p);
//         l1(k, kp1p) += s*x(kp1p);
//         l1(k, kp1p) *= rc;
//         x(kp1p)=  x(kp1p)*c-s*l1(k, kp1p);
//       }
//       assign_swap( boost::proto::child_c<0>(a1), l1);
//       return 0;
//     }


//     BOOST_FORCEINLINE
//     std::size_t update(A0& a0, A1 & a1
//                           , N1 const &
//                           , nt2::tag::minus_ const &
//                           ) const
//     {
//       container::table<value_t> l1 = boost::proto::child_c<0>(a0);
//       container::table<value_t> x  = rowvect(boost::proto::child_c<1>(a0));
//       std::size_t p = length(x);
//       if (globalany(is_lez(diag_of(l1))))
//       {
//         boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
//         error(2, N1());
//         return 2;
//       }
//       for(std::size_t k = 1; k <= p; ++k)
//       {
//         value_t ll = l1(k, k);
//         value_t ll2 = sqr(ll);
//         value_t xx2 = sqr(x(k));
//         if (ll2 > xx2)
//         {
//           value_t r =  realsqrt(ll2 - xx2);
//           value_t c =  r/ll;
//           value_t rc =  rec(c);
//           value_t s = x(k)/ll;
//           l1(k, k) = r;
//           auto kp1p = _(k+1, p);
//           l1(k, kp1p) -= s*x(kp1p);
//           l1(k, kp1p) *= rc;
//           x(kp1p)=  x(kp1p)*c-s*l1(k, kp1p);
//         }
//         else
//         {
//           boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
//           error(1, N1());
//           return 1;
//         }
//       }
//       assign_swap( boost::proto::child_c<0>(a1), l1);
//       return 0;
//     }

  };
} }

#endif

