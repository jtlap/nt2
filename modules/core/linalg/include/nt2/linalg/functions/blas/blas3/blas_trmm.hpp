//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_BLAS3_TRMM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_BLAS3_TRMM_HPP_INCLUDED

#include <nt2/linalg/functions/blas_trmm.hpp>
#include <nt2/linalg/details/blas/blas3.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/sdk/memory/container.hpp>

namespace nt2 { namespace ext
{

// /---------------------------------------------Real-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_trmm_, tag::cpu_
                            , (SIDE)(UPLO)(TRANS)(DIAG)(ALPHA)(A)(SA)(B)(SB)
                            , (scalar_<int8_<SIDE>>)// side
                              (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<int8_<DIAG>>)// diag
                              (scalar_<single_<ALPHA>>)//alpha
                              ((container_<nt2::tag::table_,  single_<A>, SA >)) //a
                              ((container_<nt2::tag::table_,  single_<B>, SB >)) //b
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const SIDE& side
                                     , const UPLO& uplo
                                     , const TRANS& trans
                                     , const DIAG& diag
                                     , const ALPHA& alpha
                                     , const A& a
                                     , B& b
                                     ) const
    {
      nt2_la_int m = height(b);
      nt2_la_int n = width(b);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldb = b.leading_size();
      NT2_F77NAME(strmm) (&side, &uplo, &trans, &diag, &m, &n, &alpha, a.data(), &lda, b.data(), &ldb);
    }
  };

// /---------------------------------------------Real-double------------------------------------------------//
  BOOST_DISPATCH_IMPLEMENT  ( blas_trmm_, tag::cpu_
                            , (SIDE)(UPLO)(TRANS)(DIAG)(ALPHA)(A)(SA)(B)(SB)
                            , (scalar_<int8_<SIDE>>)// side
                              (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<int8_<DIAG>>)// diag
                              (scalar_<double_<ALPHA>>)//alpha
                              ((container_<nt2::tag::table_,  double_<A>, SA >)) //a
                              ((container_<nt2::tag::table_,  double_<B>, SB >)) //b
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const SIDE& side
                                     , const UPLO& uplo
                                     , const TRANS& trans
                                     , const DIAG& diag
                                     , const ALPHA& alpha
                                     , const A& a
                                     , B& b
                                     ) const
    {
      nt2_la_int m = height(b);
      nt2_la_int n = width(b);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldb = b.leading_size();
      NT2_F77NAME(dtrmm)  (&side, &uplo, &trans, &diag, &m, &n, &alpha, a.data(), &lda, b.data(), &ldb);
    }
  };



// /---------------------------------------------Complex-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_trmm_, tag::cpu_
                            , (SIDE)(UPLO)(TRANS)(DIAG)(ALPHA)(A)(SA)(B)(SB)
                            , (scalar_<int8_<SIDE>>)// side
                              (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<int8_<DIAG>>)// diag
                              (scalar_<complex_<single_<ALPHA>>>)//alpha
                              ((container_<nt2::tag::table_, complex_<single_<A>>, SA >)) //a
                              ((container_<nt2::tag::table_, complex_<single_<B>>, SB >)) //c
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const SIDE& side
                                     , const UPLO& uplo
                                     , const TRANS& trans
                                     , const DIAG& diag
                                     , const ALPHA& alpha
                                     , const A& a
                                     , B& b
                                     ) const
    {
      nt2_la_int m = height(b);
      nt2_la_int n = width(b);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldb = b.leading_size();
      NT2_F77NAME(ctrmm)  (&side, &uplo, &trans, &diag, &m, &n, &alpha, a.data(), &lda, b.data(), &ldb);
    }
  };

// /---------------------------------------------Complex-double------------------------------------------------//
  BOOST_DISPATCH_IMPLEMENT  ( blas_trmm_, tag::cpu_
                            , (SIDE)(UPLO)(TRANS)(DIAG)(ALPHA)(A)(SA)(B)(SB)
                            , (scalar_<int8_<SIDE>>)// side
                              (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<int8_<DIAG>>)// diag
                              (scalar_<complex_<double_<ALPHA>>>)//alpha
                              ((container_<nt2::tag::table_, complex_<double_<A>>, SA >)) //a
                              ((container_<nt2::tag::table_, complex_<double_<B>>, SB >)) //c
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const SIDE& side
                                     , const UPLO& uplo
                                     , const TRANS& trans
                                     , const DIAG& diag
                                     , const ALPHA& alpha
                                     , const A& a
                                     , B& b
                                     ) const
    {
      nt2_la_int m = height(b);
      nt2_la_int n = width(b);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldb = b.leading_size();
      NT2_F77NAME(ztrmm)  (&side, &uplo, &trans, &diag, &m, &n, &alpha, a.data(), &lda, b.data(), &ldb);
    }
  };


} }

#endif
