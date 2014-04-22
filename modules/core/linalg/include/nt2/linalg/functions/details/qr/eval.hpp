//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_DETAILS_QR_EVAL_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_DETAILS_QR_EVAL_HPP_INCLUDED

#include <nt2/include/functions/geqp3.hpp>
#include <nt2/include/functions/geqrf.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/linalg/functions/details/extract_qr.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/sdk/meta/concrete.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - compute a full QR matrix with pivoting
  template<typename W,typename type_t> BOOST_FORCEINLINE
  nt2_la_int eval_qrfull( W& work
                        , nt2::container::table<type_t>& tau
                        , nt2::container::table<nt2_la_int>& ip
                        , nt2::policy<ext::pivot_> const&
                        )
  {
    ip = nt2::zeros(nt2::width(work),1,nt2::meta::as_<nt2_la_int>());

    return nt2::geqp3( boost::proto::value(work),  boost::proto::value(ip)
                   ,  boost::proto::value(tau) );
  }

  /// INTERNAL ONLY - compute a full QR matrix without  pivoting
  template<typename W,typename type_t> BOOST_FORCEINLINE
  nt2_la_int eval_qrfull( W& work
                        , nt2::container::table<type_t>& tau
                        , nt2::policy<ext::no_pivot_> const&
                        )
  {
    return nt2::geqrf( boost::proto::value(work),  boost::proto::value(tau));
  }

  /// INTERNAL ONLY - compute a full QR matrix with pivoting
  template<typename W,typename type_t> BOOST_FORCEINLINE
  nt2_la_int eval_qrfull( W& work
                        , nt2::container::table<type_t>& tau
                        , nt2::container::table<nt2_la_int>& /*ip*/
                        , nt2::policy<ext::no_pivot_> const&
                        )
  {
    return nt2::geqrf( boost::proto::value(work), boost::proto::value(tau));
  }

  /// INTERNAL ONLY - compute a full QR matrix with pivoting
  template<typename W,typename type_t> BOOST_FORCEINLINE
  nt2_la_int eval_qrfull( W& work
                        , nt2::container::table<type_t>& tau
                        , nt2::container::table<nt2_la_int>& ip
                        , nt2::policy<ext::matrix_> const&
                        )
  {
    ip = nt2::zeros(nt2::width(work),1,nt2::meta::as_<nt2_la_int>());

    return nt2::geqp3( boost::proto::value(work), boost::proto::value(ip)
                   , boost::proto::value(tau) );
  }

  /// INTERNAL ONLY - compute a full QR matrix with pivoting
  template<typename W,typename type_t> BOOST_FORCEINLINE
  nt2_la_int eval_qrfull( W& work
                        , nt2::container::table<type_t>& tau
                        , nt2::container::table<nt2_la_int>& ip
                        , int const&
                        )
  {
    ip = nt2::zeros(nt2::width(work),1,nt2::meta::as_<nt2_la_int>());

    return nt2::geqp3( boost::proto::value(work), boost::proto::value(ip)
                   , boost::proto::value(tau) );
  }

  /// INTERNAL ONLY - compute a full QR matrix with pivoting
  template<typename W,typename type_t> BOOST_FORCEINLINE
  nt2_la_int eval_qrfull( W& work
                        , nt2::container::table<type_t>& tau
                        , nt2::container::table<nt2_la_int>& ip
                        , nt2::policy<ext::vector_> const&
                        )
  {
    ip = nt2::zeros(nt2::width(work),1,nt2::meta::as_<nt2_la_int>());

    return nt2::geqp3( boost::proto::value(work), boost::proto::value(ip)
                   , boost::proto::value(tau) );
  }

  template<typename A0, typename A1,typename Policy,typename type_t>
  BOOST_FORCEINLINE
  void eval_qr( A0& a0, A1& a1
              , nt2::container::table<type_t>& tau
              , nt2::container::table<nt2_la_int>& ip
              , Policy const& p
              )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::type  c0_t;
    typedef typename meta::concrete<c0_t>::type                     c_t;

    ip = nt2::zeros(nt2::width(a0),1,nt2::meta::as_<nt2_la_int>());

    c_t work = shallow_concrete ( boost::proto::child_c<0>(a1)
                                , boost::proto::child_c<0>(a0)
                                );

    nt2_la_int info = eval_qrfull( work, tau, ip, p);
    boost::dispatch::ignore_unused(info);

    extract_qr(a1,work,tau,p);
  }

  template<typename A0, typename A1,typename Policy,typename type_t>
  BOOST_FORCEINLINE
  void eval_qr( A0& a0, A1& a1
              , nt2::container::table<type_t>& tau
              , Policy const& p
              )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::type  c0_t;
    typedef typename meta::concrete<c0_t>::type                     c_t;

    c_t work = shallow_concrete ( boost::proto::child_c<0>(a1)
                                , boost::proto::child_c<0>(a0)
                                );

    nt2_la_int info = eval_qrfull( work, tau, nt2::policy<ext::no_pivot_>());
    boost::dispatch::ignore_unused(info);

    extract_qr(a1,work,tau,p);
  }
} }

#endif
