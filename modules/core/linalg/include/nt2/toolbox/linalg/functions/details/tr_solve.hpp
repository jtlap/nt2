/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_TR_SOLVE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_TR_SOLVE_HPP_INCLUDED
#include <nt2/include/functions/tr_solve.hpp>
#include <nt2/toolbox/linalg/details/lapack/trtrs.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/istriangular.hpp>
#include <nt2/include/functions/ofsameheight.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/sdk/error/warning.hpp>
namespace nt2 {namespace details
{
  //============================================================================
  // tr actual functor : precompute
  //============================================================================
  template<class A, class B = A> struct tr_solve_result
  {
    typedef typename meta::strip<A>::type             strip_t;
    typedef typename strip_t::value_type               type_t;
    typedef typename strip_t::index_type              index_t;
    typedef typename meta::as_real<type_t>::type      btype_t;
    typedef nt2::table<type_t,nt2::matlab_index_>      ftab_t;
    typedef nt2::table<btype_t,nt2::matlab_index_>    fbtab_t;
    typedef nt2::table<nt2_la_int,nt2::matlab_index_> fitab_t;
    typedef nt2::table<type_t,index_t>                  tab_t;
    typedef nt2::table<btype_t,index_t>                btab_t;
    typedef nt2::table<nt2_la_int,index_t>             itab_t;
    typedef A                                         data1_t;
    typedef B                                         data2_t;

    ////////////////////////////////////////////////////////////////////////////
    //  Solve triangular systems
    //  A is            N x N
    //  X is            N x nrhs
    //  need sentimentally a triangular matrix. Only the lower
    //  triangular part is used by default (uplo = 'l' : use 'u' to get the
    //  upper part used)
    //  solve a*xx =  b, use trans = 't' to solve trans(a)*xx = b
    //  do not assume diag elements are special, use diag = 'u' to suppose ones
    //  on the diagonal and no access to a diagonal elements
    ////////////////////////////////////////////////////////////////////////////
    template < class Input1, class Input2>
    tr_solve_result(Input1& a,
                    Input2& bx,
                    const char& uplo  /*= 'l'*/,
                    const char& trans /*= 'n'*/,
                    const char& diag  /*= 'n'*/ )
      : a_(a),
        bx_(bx)
    {
      NT2_WARNING(nt2::istriangular(a_)||(uplo == 'L'), "in tr_solve input is not triangular: only the upper matrix part will be used");
      NT2_WARNING(nt2::istriangular(a_)||(uplo == 'U'), "in tr_solve input is not triangular: only the lower matrix part will be used");
      BOOST_ASSERT_MSG(nt2::issquare(a), "matrix a is not square");
      BOOST_ASSERT_MSG(nt2::ofsameheight(a_, bx_), "a and x have different heights");
      const nt2_la_int m = height(a_);
      const nt2_la_int k = width(bx_);
      const nt2_la_int lda = a_.leading_size();
      const nt2_la_int ldx = bx_.leading_size();
      nt2::details::trtrs(&uplo, &trans, &diag, &m, &k,
                          a_.raw(), &lda, bx_.raw(), &ldx, &info_);
    }
    ~tr_solve_result(){}
    ftab_t x()             const { return bx_;   }
    ftab_t values()        const { return a_;    }
    nt2_la_int status()    const { return info_; }
  private:
    data1_t        a_;
    data2_t       bx_;
    nt2_la_int  info_;

  };
} }
#endif

// /////////////////////////////////////////////////////////////////////////////
// End of tr_solve.hpp
// /////////////////////////////////////////////////////////////////////////////
