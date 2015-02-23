//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_QR_QR_KERNEL_HPP_INCLUDED
#define NT2_LINALG_DETAILS_QR_QR_KERNEL_HPP_INCLUDED
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/fms.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/planerot.hpp>
#include <nt2/trigonometric/include/functions/sincos.hpp>//just for the tag
#include <nt2/include/constants/zero.hpp>
#include <nt2/core/container/extremum/extremum.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/utility/assign_swap.hpp>

namespace nt2 { namespace details
{
  template < class value_t > struct qr_kernel
  {

    typedef typename meta::as_real<value_t>::type                   rvalue_t;

    // retriangularize and store cosine and sine
    template < class R,  class C, class S>
    static BOOST_FORCEINLINE
    void retriangularize(std::size_t m, std::size_t n, R& r, C& c, S& s)
    {
      for(std::size_t i=1; i <= n; ++i)
      {
        value_t t = r(1, i);
        const std::size_t ii = nt2::min(m,i);
        for(std::size_t j=1; j < ii ; ++j)
        {
          r(j,i) = fma(c(j), t, s(j)*r(j+1,i));
          t = fms(c(j), r(j+1,i), conj(s(j))*t);
        }
        if (ii < m)
        {
          tie(s(i), c(i), r(ii,i)) = planerot(cons(of_size(2, 1), t,r(ii+1,i)),
                                              nt2::tag::sincos_());
          r(ii+1, i) = Zero<value_t>();
        }
        else
        {
          r(ii, i) = t;
        }
      }
    }
    template < class Q,  class C, class S>
    static BOOST_FORCEINLINE
    void rotate_backward(std::size_t n, Q& q, const C& c, const S& s)
    {
      auto cs =  conj(s);
      for(std::size_t i=n-1; i >= 1u; --i)//backward
      {
        auto ru = q(_, i);
        auto rv = q(_, i+1);
        container::table<value_t> temp = fma(c(i), ru, cs(i)*rv);
        rv = fms(c(i), rv, s(i)*ru);
        ru = temp;
      }
    }

    template < class Q,  class C, class S>
    static BOOST_FORCEINLINE
    void rotate_forward(std::size_t n, Q& q
                       , const C& c, const S& s)
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
    // generates a sequence of n-1 Givens rotations that
    //               eliminate all but the first element of a vector u.
    template < class U,  class W> //*
    static BOOST_FORCEINLINE
    void mkzeroingrots(size_t n, U& u,  W& w)
    {
      value_t rr = u(n), t;
      for(std::size_t i=n-1; i >= 1 ; --i)
      {
         tie(u(i+1), w(i), t) = planerot(cons(of_size(2, 1), u(i), rr)
                                        , nt2::tag::sincos_());
        rr = t;
      }
      u(1) = rr;
    }

    //brings an upper trapezoidal matrix R into upper
    //Hessenberg form using planar rotations.
    template < class R,  class C, class S>
    static BOOST_FORCEINLINE
    void mkhessenberg(std::size_t m, std::size_t n, R& r
                     , const C& c, const S& s)
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

    template < class A, class Q,  class R>
    static BOOST_FORCEINLINE
    void finalize(A& a1, Q& q, R& r)
    {
      assign_swap(boost::proto::child_c<0>(a1), q);
      assign_swap(boost::proto::child_c<1>(a1), r);
    }
  };
} }
#endif

