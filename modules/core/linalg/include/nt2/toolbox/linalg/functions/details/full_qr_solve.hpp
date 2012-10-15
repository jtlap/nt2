/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_FULL_QR_SOLVE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_FULL_QR_SOLVE_HPP_INCLUDED

#include <nt2/toolbox/linalg/details/lapack/gelsy.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/sdk/error/warning.hpp>
namespace nt2 { namespace details
{
  //============================================================================
  // full_qr_solve actual functor
  //============================================================================
  template<class A> struct full_qr_solve_result
  {
    typedef typename meta::strip<A>::type               strip_t;
    typedef typename strip_t::value_type                 type_t;
    typedef typename strip_t::index_type                index_t;
    typedef typename meta::as_real<type_t>::type        btype_t;
    typedef nt2::table<type_t,nt2::matlab_index_>        ftab_t;
    typedef nt2::table<btype_t,nt2::matlab_index_>      fbtab_t;
    typedef nt2::table<nt2_la_int,nt2::matlab_index_>   fitab_t;
    typedef nt2::table<type_t,index_t>                    tab_t;
    typedef nt2::table<btype_t,index_t>                  btab_t;
    typedef nt2::table<nt2_la_int,index_t>               itab_t;
    typedef A                                            data_t;

    ////////////////////////////////////////////////////////////////////////////
    // General QR Solver
    //  A is            N x M
    //  B is            N x nrhs
    ////////////////////////////////////////////////////////////////////////////
    template < class Input, class B >
    full_qr_solve_result(Input& a, const B& b, const char &/*trans*/, const type_t& rcond = type_t(0))
      : a_(a)
      , lda_(a_.leading_size())
      , ldb_(b.leading_size())
      , m_(height(a))
      , n_(width(a))
      , nrhs_(width(b))
      , x_(nt2::expand(b, nt2::max(n_, m_), nrhs_))
      , jpvt_(nt2::zeros(n_, 1, nt2::meta::as_<nt2_la_int>()))
    {
      nt2_la_int ldx  = x_.leading_size();
      nt2::details::gelsy (&m_, &n_, &nrhs_, a_.raw(), &lda_,
                           x_.raw(), &ldx, jpvt_.raw(), &rcond,
                           &rank_, &info_);
      //      NT2_WARNING(info_ <= 0, "Warning: Matrix is singular to working precision.");
    }

    fitab_t ipiv()      const { return jpvt_; }
    //    btype_t rcond()     const { return rcond_;}
    nt2::int32_t rank() const { return rank_; }
    nt2_la_int status() const { return info_; }
    tab_t  x()          const { return x_;    }
  private:
    data_t                a_;
    nt2_la_int          lda_;
    nt2_la_int          ldb_;
    nt2_la_int            m_;
    nt2_la_int            n_;
    nt2_la_int         nrhs_;
    tab_t                 x_;
    fitab_t            jpvt_;
    nt2_la_int         info_;
    //    btype_t           rcond_;
    nt2::int32_t       rank_;
  };
} }


#endif
