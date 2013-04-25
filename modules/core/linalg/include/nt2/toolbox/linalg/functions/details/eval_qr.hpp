//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_EVAL_QR_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_EVAL_QR_HPP_INCLUDED



#include <nt2/include/functions/qp3.hpp>
#include <nt2/include/functions/qrf.hpp>
#include <nt2/toolbox/linalg/options.hpp>
#include <nt2/toolbox/linalg/functions/details/extract_qr.hpp>
#include <nt2/core/container/dsl/forward.hpp>

namespace nt2{ namespace ext
  {

    /// INTERNAL ONLY - compute a full QR matrix with pivoting
    template<typename W,typename type_t> BOOST_FORCEINLINE
    nt2_la_int eval_qrfull( W& work
                          , nt2::container::table<type_t>& tau
                          , nt2::container::table<nt2_la_int>& ip
                          , nt2::policy<ext::pivot_> const&
                          )
    {
      return nt2::qp3(work, ip, tau);
    }

    /// INTERNAL ONLY - compute a full QR matrix without  pivoting
    template<typename W,typename type_t> BOOST_FORCEINLINE
    nt2_la_int eval_qrfull( W& work
                          , nt2::container::table<type_t>& tau
                          , nt2::policy<ext::no_pivot_> const&
                          )
    {
      return nt2::qrf(work, tau);
    }

    /// INTERNAL ONLY - compute a full QR matrix with pivoting
    template<typename W,typename type_t> BOOST_FORCEINLINE
    nt2_la_int eval_qrfull( W& work
                          , nt2::container::table<type_t>& tau
                          , nt2::container::table<nt2_la_int>& ip
                          , nt2::policy<ext::no_pivot_> const&
                          )
    {
      return nt2::qrf(work, tau);
    }

    /// INTERNAL ONLY - compute a full QR matrix with pivoting
    template<typename W,typename type_t> BOOST_FORCEINLINE
    nt2_la_int eval_qrfull( W& work
                          , nt2::container::table<type_t>& tau
                          , nt2::container::table<nt2_la_int>& ip
                          , nt2::policy<ext::matrix_> const&
                          )
    {
      return nt2::qp3(work, ip, tau);
    }

    /// INTERNAL ONLY - compute a full QR matrix with pivoting
    template<typename W,typename type_t> BOOST_FORCEINLINE
    nt2_la_int eval_qrfull( W& work
                          , nt2::container::table<type_t>& tau
                          , nt2::container::table<nt2_la_int>& ip
                          , int const&
                          )
    {
      return nt2::qp3(work, ip, tau);
    }

    /// INTERNAL ONLY - compute a full QR matrix with pivoting
    template<typename W,typename type_t> BOOST_FORCEINLINE
    nt2_la_int eval_qrfull( W& work
                          , nt2::container::table<type_t>& tau
                          , nt2::container::table<nt2_la_int>& ip
                          , nt2::policy<ext::vector_> const&
                          )
    {
      return nt2::qp3(work, ip, tau);
    }

    template<typename A0, typename A1,typename Policy,typename type_t>
    BOOST_FORCEINLINE
    void eval_qr( A0& a0, A1& a1
                , nt2::container::table<type_t>& tau
                , nt2::container::table<nt2_la_int>& ip
                , Policy const& p
                )
    {
      BOOST_AUTO_TPL( work, concrete(boost::proto::child_c<0>(a1)) );
      work = boost::proto::child_c<0>(a0);

      nt2_la_int info = eval_qrfull( work, tau, ip, p);

      extract_qr(a1,work,tau,p);
    }

    template<typename A0, typename A1,typename Policy,typename type_t>
    BOOST_FORCEINLINE
    void eval_qr( A0& a0, A1& a1
                , nt2::container::table<type_t>& tau
                , Policy const& p
                )
    {
      BOOST_AUTO_TPL( work, concrete(boost::proto::child_c<0>(a1)) );
      work = boost::proto::child_c<0>(a0);

      nt2_la_int info = eval_qrfull( work, tau, nt2::policy<ext::no_pivot_>());

      extract_qr(a1,work,tau,p);
    }

} }


#endif
