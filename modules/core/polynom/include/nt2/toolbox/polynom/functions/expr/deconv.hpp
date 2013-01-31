//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_POLYNOM_FUNCTIONS_EXPR_DECONV_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOM_FUNCTIONS_EXPR_DECONV_HPP_INCLUDED
#include <nt2/toolbox/polynom/functions/deconv.hpp>

#include <nt2/core/container/table/table.hpp>

#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/eye.hpp>

// #include <nt2/include/functions/scalar/fma.hpp>
// #include <nt2/include/functions/zeros.hpp>
// #include <nt2/include/functions/numel.hpp>
// #include <nt2/include/functions/eye.hpp>
// #include <nt2/include/functions/colvect.hpp>
// #include <nt2/include/functions/rowvect.hpp>
// #include <nt2/include/functions/linsolve.hpp>
// #include <nt2/include/functions/tie.hpp>

namespace nt2 { namespace ext
{

  //============================================================================
  // This version of balance is called whenever a tie(...) = balance(...) is captured
  // before assign is resolved. As a tieable function, balance retrieves rhs/lhs
  // pair as inputs
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::deconv_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::deconv_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       q_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::type       a_type;
    typedef typename boost::proto::result_of::child_c<A0&,1>::type       b_type;
    typedef typename A0::value_type                                         v_t;
    typedef typename nt2::container::table<v_t, nt2::_2D>                 tab_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      compute(a0, a1, N1());
    }

  private:
    template < class N >
    BOOST_FORCEINLINE void compute(A0& a0, A1& a1,N const & n1) const
    {
      a_type  a = boost::proto::child_c<0>(a0);
      b_type  b = boost::proto::child_c<1>(a0);
      size_t na =  nt2::numel(a);
      size_t nb =  nt2::numel(b);
      q_type  qr = boost::proto::child_c<0>(a1);
      size_t nq;
      if(na < nb)
      {
        nq = 0;
        qr = b;
      }
      else
      {
        nq =  na+1-nb;
        tab_t m =   nt2::eye(numel(a),meta::as_<v_t>());
        for(size_t i=1; i <= nq; ++i)
        {
          m(nt2::_(i, (i-1)+nb), i) = nt2::colvect(b);
        }
        tab_t bb = nt2::linsolve(m, nt2::colvect(a));
        qr = nt2::rowvect(bb);
      }
      get_values(a1,qr,nq,n1);
    }

    void get_values(A1& a1, q_type qr, const size_t& nq, boost::mpl::long_<1> const &) const
    {
      qr.resize(nt2::of_size(1, nq));
    }
    void get_values(A1& a1, q_type qr, const size_t& nq, boost::mpl::long_<2> const &) const
    {
      typedef typename boost::proto::result_of::child_c<A1&,1>::type r_type;
      r_type  r = boost::proto::child_c<1>(a1);
      r = qr(nt2::_(nq+1, nt2::end_));
      qr.resize(nt2::of_size(1, nq));
    }
  };
} }


#endif
