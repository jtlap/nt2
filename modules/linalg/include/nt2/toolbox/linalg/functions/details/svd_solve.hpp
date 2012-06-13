/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_SVD_SOLVE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_SVD_SOLVE_HPP_INCLUDED


#include <nt2/include/functions/svd_solve.hpp>
#include <nt2/toolbox/linalg/details/lapack/gelsd.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/ofsameheight.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/expand.hpp>

//==============================================================================
// svd_solve actual functor
//==============================================================================

namespace nt2 { namespace details
{
  //============================================================================
  // svd actual functor : precompute
  //============================================================================
  template<class A> struct svd_solve_result
  {
    typedef typename meta::strip<A>::type             strip_t;
    typedef typename strip_t::value_type               type_t;
    typedef typename strip_t::index_type              index_t;
    typedef typename meta::as_real<type_t>::type      rtype_t;
    typedef nt2::table<type_t,nt2::matlab_index_>      ftab_t;
    typedef nt2::table<rtype_t,nt2::matlab_index_>    fbtab_t;
    typedef nt2::table<nt2_la_int,nt2::matlab_index_> fitab_t;
    typedef nt2::table<type_t,index_t>                  tab_t;
    typedef nt2::table<rtype_t,index_t>                rtab_t;
    typedef nt2::table<nt2_la_int,index_t>             itab_t;
    typedef A                                          data_t;

    ////////////////////////////////////////////////////////////////////////////
    // General SVD solver
    //  A is            M x N            may be rank-deficient
    //  X is or will be N x nrhs
    //  B is            M x nrhs
    ////////////////////////////////////////////////////////////////////////////
    template < class Input, class B>
    svd_solve_result(Input& a,
                     const B& b,
                     const rtype_t & rcond = rtype_t(-1))
      : a_(a)
    {
      const nt2_la_int ml   = size(a_, 1);
      const nt2_la_int nl   = size(a_, 2);
      const nt2_la_int nrhs = size(b, 2);
      const nt2_la_int lda  = a_.leading_size();
      const nt2_la_int ldb  = b.leading_size();
      rtab_t s(of_size(nt2::min(ml, nl), 1));

      // typically is a non-square, so we need to create tmp x because is
      //  x is n x nrhs, while b is m x nrhs.  we need to make copies of
      //  these so that the routine won't corrupt data around x and b

      if (ml != nl)
        {
          nt2_la_int mm =  std::max(std::max(ml,nl),1);
          x_ = nt2::expand(b, nt2::of_size(mm, nrhs));
          nt2_la_int ldx_ =  x_.leading_size();
          nt2::details::gelsd(&ml, &nl, &nrhs, a_.raw(), &lda, x_.raw(), &ldx_,
                              s.raw(), &rcond, &rank_, &info_);
          x_ = x_(_(1, nl), _(1, nrhs));
          //          BOOST_ASSERT_MSG(info!= 0, "lapack error : gelsd in solve_svd_ip(1)");
        }
      else
        {
          x_ = b;
          nt2_la_int ldx_ =  x_.leading_size();
          nt2::details::gelsd(&ml, &nl, &nrhs, a_.raw(), &lda, x_.raw(), &ldx_,
                              s.raw(), &rcond, &rank_, &info_);
          //          BOOST_ASSERT_MSG(info == 0, "lapack error : gelsd in solve_svd_ip(2)");
        }
    }
    ~svd_solve_result(){}
    tab_t     x()          const { return x_; }
    nt2_la_int rank()      const { return rank_; }
    nt2_la_int status()    const { return info_; }
  private:
    data_t                  a_;
    ftab_t                  x_;
    nt2_la_int           rank_;
    nt2_la_int           info_;
  };
} }

#endif

