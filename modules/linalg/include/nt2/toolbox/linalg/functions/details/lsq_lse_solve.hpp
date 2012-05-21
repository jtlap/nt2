/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_LSQ_LSE_SOLVE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_LSQ_LSE_SOLVE_HPP_INCLUDED

#include <nt2/include/functions/lsq_lse_solve.hpp>
#include <nt2/toolbox/linalg/details/lapack/gglse.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
//  **          minimize || c - a*x ||_2   subject to   b*x = d
namespace nt2 {namespace details
{
  //============================================================================
  // lse actual functor : precompute
  //============================================================================
  template<class A, class B = A, class C = B, class D = C> struct lsq_lse_solve_result
  {
    typedef typename meta::strip<A>::type              base_t;
    typedef typename base_t::value_type                type_t;
    typedef typename base_t::index_type               index_t;
    typedef typename meta::as_real<type_t>::type      rtype_t;
    typedef nt2::table<type_t,nt2::matlab_index_>      ftab_t;
    typedef nt2::table<rtype_t,nt2::matlab_index_>    fbtab_t;
    typedef nt2::table<nt2_la_int,nt2::matlab_index_> fitab_t;
    typedef nt2::table<type_t,index_t>                  tab_t;
    typedef nt2::table<rtype_t,index_t>                rtab_t;
    typedef nt2::table<nt2_la_int,index_t>             itab_t;
    typedef A                                             a_t;
    typedef B                                             b_t;
    typedef C                                             c_t;
    typedef D                                             d_t;

    ////////////////////////////////////////////////////////////////////////////
    // general lse solver
    //  a is            m x n
    //  x       will be n x 1
    //  b is            p x n
    //  catv(a, b) is assumed to be of rank n
    ////////////////////////////////////////////////////////////////////////////
    template < class I1, class I2, class I3, class I4>
    lsq_lse_solve_result(I1& a, I2& b, I3&c, I4&d)
      : a_(a)
      , b_(b)
      , c_(c)
      , d_(d)
      , x_(of_size(nt2::width(a_), 1))
      , m_(nt2::height(a_))
      , n_(nt2::width(a_))
      , p_(nt2::height(b_))

    {
      nt2_la_int lda = a_.leading_size();
      nt2_la_int ldb = b_.leading_size();
      BOOST_ASSERT_MSG( (n_ == nt2::width(b_)),"In lse calls the number of columns of a must match the number of columns of b");
      BOOST_ASSERT_MSG( (n_ >= p_),"In lse calls the number of columns of a must be greater or equal to the number of rows of b");
      BOOST_ASSERT_MSG( (n_ <= m_+p_),"In lse calls n <= m+p");
      BOOST_ASSERT_MSG( (p_ == nt2::numel(d_)),"In lse calls the number of rows of b must match the number of elements of d");
      nt2::details::gglse(&m_, &n_, &p_, a_.raw(), &lda, b_.raw(), &ldb, c_.raw(), d_.raw(), x_.raw(), &info_);
    }
    ~lsq_lse_solve_result(){}
    nt2_la_int status()    const { return info_; }
    ftab_t x()           const { return x_;              }
    ftab_t residuals()   const { return c_(_(begin_+(n_-p_), end_)); }
  private:
    a_t                  a_;
    b_t                  b_;
    c_t                  c_;
    d_t                  d_;
    tab_t                x_;
    nt2_la_int           m_;
    nt2_la_int           n_;
    nt2_la_int           p_;
    nt2_la_int        info_;
  };
} }

#endif
