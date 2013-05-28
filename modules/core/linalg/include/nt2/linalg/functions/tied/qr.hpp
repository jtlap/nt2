//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_QR_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_QR_HPP_INCLUDED


#include <nt2/linalg/functions/details/eval_qr.hpp>
#include <nt2/linalg/functions/details/pivot_qr.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/sdk/meta/concrete.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  //[Q,R] = QR(A)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qr_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::qr_
                                    , N0, nt2::container::domain
                                      >
                              ))
                              ((node_<A1, nt2::tag::tie_
                                    , N1, nt2::container::domain
                                     >
                              ))
                            )
  {
    typedef void  result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::value_type c0_t;
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type child0;
    typedef typename child0::value_type type_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      nt2::table<nt2_la_int>  ip;
      nt2::table<type_t>      tau;
      eval(a0, a1, tau, ip, N0(), N1());
    }

    //==========================================================================
    /// INTERNAL ONLY - X = QR(A)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , nt2::table<type_t>& tau     , nt2::table<nt2_la_int>& ip
              , boost::mpl::long_<1> const& , boost::mpl::long_<1> const&
              ) const
    {
      BOOST_AUTO_TPL( work, concrete(boost::proto::child_c<0>(a1)) );
      work = boost::proto::child_c<0>(a0);

      nt2_la_int info = eval_qrfull(work, tau, ip, nt2::policy<ext::pivot_>());

      boost::proto::child_c<0>(a1) = work;
    }

    /// INTERNAL ONLY - [Q,R] = QR(A)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , nt2::table<type_t>& tau, nt2::table<nt2_la_int>& ip
              , boost::mpl::long_<1> const&, boost::mpl::long_<2> const&
              ) const
    {
      eval_qr( a0, a1, tau, nt2::policy<ext::no_pivot_>() );
    }

    /// INTERNAL ONLY - [Q,R,P] = QR(A)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , nt2::table<type_t>& tau, nt2::table<nt2_la_int>& ip
              , boost::mpl::long_<1> const&, boost::mpl::long_<3> const&
              ) const
    {
      eval_qr( a0, a1, tau, ip, nt2::policy<ext::pivot_>());
      extract_p(a1,ip,nt2::policy<ext::matrix_>());
    }

    //==========================================================================
    /// INTERNAL ONLY - X = QR(A,{0/{no_}pivot_})
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , nt2::table<type_t>& tau, nt2::table<nt2_la_int>& ip
              , boost::mpl::long_<2> const&, boost::mpl::long_<1> const&
              ) const
    {
      BOOST_AUTO_TPL( work, concrete(boost::proto::child_c<0>(a1)) );
      work = boost::proto::child_c<0>(a0);

      eval_qrfull(work,tau,ip,boost::proto::value(boost::proto::child_c<1>(a0)));
      boost::proto::child_c<0>(a1) = work;

    }

    //==========================================================================
    /// INTERNAL ONLY - [Q,R] = QR(A,{0/{no_}pivot_})
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , nt2::table<type_t>& tau, nt2::table<nt2_la_int>& ip
              , boost::mpl::long_<2> const&, boost::mpl::long_<2> const&
              ) const
    {
      eval_qr(a0,a1,tau,boost::proto::value(boost::proto::child_c<1>(a0)) );
    }

    // //=============== ===========================================================
    /// INTERNAL ONLY - [Q,R,P] = QR(A,{0/matrix/vector)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , nt2::table<type_t>& tau, nt2::table<nt2_la_int>& ip
              , boost::mpl::long_<2> const&, boost::mpl::long_<3> const&
              ) const
    {
      BOOST_AUTO_TPL( p, boost::proto::value(boost::proto::child_c<1>(a0)) );
      eval_qr(a0,a1,tau,ip,p);
      extract_p(a1,ip,p);
    }


  };
} }


#endif
