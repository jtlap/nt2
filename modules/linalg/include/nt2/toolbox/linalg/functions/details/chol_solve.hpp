/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_CHOL_SOLVE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_CHOL_SOLVE_HPP_INCLUDED

#include <nt2/include/functions/chol_solve.hpp>
#include <nt2/toolbox/linalg/details/lapack/posv.hpp>   
#include <nt2/table.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/ofsameheight.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <iostream>

namespace nt2 { namespace details
{
  //============================================================================
  // chol_solve actual functor 
  //============================================================================
  template<class A, class B = A> struct chol_solve_result
  {
    typedef typename A::value_type                      type_t;
    typedef typename A::index_type                     index_t; 
    typedef typename meta::as_real<type_t>::type       btype_t; 
    typedef nt2::table<type_t,nt2::matlab_index_>       ftab_t;
    typedef nt2::table<btype_t,nt2::matlab_index_>     fbtab_t;
    typedef nt2::table<nt2_la_int,nt2::matlab_index_>  fitab_t;
    typedef nt2::table<type_t,index_t>                   tab_t;
    typedef nt2::table<btype_t,index_t>                 btab_t;
    typedef nt2::table<nt2_la_int,index_t>              itab_t;
    
    ////////////////////////////////////////////////////////////////////////////
    // general cholevski solver
    //  a is            n x n
    //  x is or will be n x nrhs
    //  b is            n x nrhs
    //  need sentimentally a symetric definite positive. Only the ower
    //  triangular part is used by default (uplo = 'l' : use 'u' to use the
    //  upper part used) 
    ////////////////////////////////////////////////////////////////////////////
    chol_solve_result(A& a, B& bx, const char & uplo  /*= 'l'*/)
      : a_(a),
        b_(bx)
    {
      BOOST_ASSERT_MSG(nt2::issquare(a_), "matrix a is not square");
      BOOST_ASSERT_MSG(nt2::ofsameheight(a_, b_), "a and x have different heights");
      const nt2_la_int m = height(a);
      const nt2_la_int k = width(bx);
      const nt2_la_int lda = a_.leading_size();
      const nt2_la_int ldx = b_.leading_size();
      nt2::details::posv(&uplo, &m, &k, a_.raw(), &lda, b_.raw(), &ldx, &info_);
    }
    ~chol_solve_result(){}
    nt2_la_int status()    const { return info_; }
    B& x() {return b_; }
  private:
    A& a_; 
    B& b_;
    nt2_la_int  info_;
  };
} }

#endif
