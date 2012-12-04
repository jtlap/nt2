/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_FULL_LU_SOLVE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_FULL_LU_SOLVE_HPP_INCLUDED

#include <nt2/toolbox/linalg/details/lapack/gesvx.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/sdk/error/warning.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // full_lu_solve actual functor
  //============================================================================
  template<class A, class B = A> struct full_lu_solve_result
  {
    typedef typename meta::strip<A>::type               strip_t;
    typedef typename strip_t::value_type                 type_t;
    typedef typename strip_t::index_type                index_t;
    typedef typename meta::as_real<type_t>::type        btype_t;
    typedef nt2::container::table<type_t,nt2::_2D>                  ftab_t;
    typedef nt2::container::table<btype_t,nt2::_2D>                fbtab_t;
    typedef nt2::container::table<nt2_la_int,nt2::_2D>             fitab_t;
    typedef nt2::container::table<type_t,index_t>                    tab_t;
    typedef nt2::container::table<btype_t,index_t>                  btab_t;
    typedef nt2::container::table<nt2_la_int,index_t>               itab_t;
    typedef A                                           data1_t;
    typedef B                                           data2_t;
    ////////////////////////////////////////////////////////////////////////////
    // General LU Solver
    //  A is            N x N
    //  B is            N x nrhs
    ////////////////////////////////////////////////////////////////////////////
    template < class Input1,  class Input2 >
    full_lu_solve_result(Input1& a, Input2& b, const char & trans)
      :
      a_(a)
      , b_(b)
      , lda_(a_.leading_size())
      , ldb_(b_.leading_size())
      , n_(height(a_))
      , nrhs_(width(b_))
      , x_(nt2::of_size(n_, nrhs_))
      , ipiv_(nt2::of_size(n_, 1))
      , af_(nt2::of_size(n_, n_))
      , ferr_( nt2::of_size(n_, 1))
      , berr_( nt2::of_size(n_, 1))
      , r_( nt2::of_size(n_, 1))
      , c_( nt2::of_size(n_, 1))
    {
      char fact = 'N';
      char equed = 'N';
      nt2_la_int ldaf = af_.leading_size();
      nt2_la_int ldx  = x_.leading_size();
      nt2::details::gesvx (&fact, &trans, &n_, &nrhs_, a_.raw(), &lda_,
                          af_.raw(), &ldaf, ipiv_.raw(), &equed,
                          r_.raw(), c_.raw(),
                          b_.raw(), &ldb_,
                          x_.raw(), &ldx, &rcond_,
                          ferr_.raw(), berr_.raw(), &info_);
      NT2_WARNING(info_ <=  0, "Warning: Matrix is singular to working precision.");
    }
    ~full_lu_solve_result(){}
    const fitab_t& ipiv()       const { return ipiv_; }
    const btype_t& rcond()     const { return rcond_;}
    nt2_la_int status() const { return info_; }
    const ftab_t&  ferr()       const { return ferr_; }
    const ftab_t&  berr()       const { return berr_; }
    const ftab_t&  x()          const { return x_;    }
  private:
    data1_t               a_;
    data2_t               b_;
    nt2_la_int          lda_;
    nt2_la_int          ldb_;
    nt2_la_int            n_;
    nt2_la_int         nrhs_;
    ftab_t                x_;
    fitab_t            ipiv_;
    nt2_la_int         info_;
    ftab_t               af_;
    fbtab_t            ferr_;
    fbtab_t            berr_;
    fbtab_t               r_;
    fbtab_t               c_;
    btype_t           rcond_;
  };
} }


#endif
