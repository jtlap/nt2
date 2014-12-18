//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_BLAS3_HER2K_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_BLAS3_HER2K_HPP_INCLUDED

#include <nt2/linalg/functions/blas_her2k.hpp>
#include <nt2/linalg/details/blas/blas3.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/sdk/memory/container.hpp>

namespace nt2 { namespace ext
{

// /---------------------------------------------Real-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_her2k_, tag::cpu_
                            , (UPLO)(TRANS)(ALPHA)(A)(SA)(B)(SB)(BETA)(C)(SC)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<single_<ALPHA>>)//alpha
                              ((container_<nt2::tag::table_,  single_<A>, SA >)) //a
                              ((container_<nt2::tag::table_,  single_<B>, SB >)) //b
                              (scalar_<single_<BETA>>)// beta
                              ((container_<nt2::tag::table_,  single_<C>, SC >)) //c
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const TRANS& trans
                                     , const ALPHA& alpha
                                     , const A& a
                                     , const B& b
                                     , const BETA beta
                                     , C& c
                                     ) const
    {
      nt2_la_int n = height(c);  //((uplo == 'N')||(uplo == 'n')) ? height(b) : width(b);
      nt2_la_int k = ((trans == 'N')||(trans == 'n')) ?  width(a) : height(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldb = b.leading_size();
      nt2_la_int ldc = c.leading_size();
      NT2_F77NAME(ssyr2k) (&uplo, &trans, &n, &k, &alpha, a.data(), &lda, b.data(), &ldb, &beta, c.data(), &ldc);
    }
  };

// /---------------------------------------------Real-double------------------------------------------------//
  BOOST_DISPATCH_IMPLEMENT  ( blas_her2k_, tag::cpu_
                            , (UPLO)(TRANS)(ALPHA)(A)(SA)(B)(SB)(BETA)(C)(SC)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<double_<ALPHA>>)//alpha
                              ((container_<nt2::tag::table_,  double_<A>, SA >)) //a
                              ((container_<nt2::tag::table_,  double_<B>, SB >)) //b
                              (scalar_<double_<BETA>>)// beta
                              ((container_<nt2::tag::table_,  double_<C>, SC >)) //c
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const TRANS& trans
                                     , const ALPHA& alpha
                                     , const A& a
                                     , const B& b
                                     , const BETA& beta
                                     , C& c
                                     ) const
    {
      nt2_la_int n = height(c);  //((uplo == 'N')||(uplo == 'n')) ? height(b) : width(b);
      nt2_la_int k = ((trans == 'N')||(trans == 'n')) ?  width(a) : height(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldb = b.leading_size();
      nt2_la_int ldc = c.leading_size();
      NT2_F77NAME(dsyr2k)  (&uplo, &trans, &n, &k, &alpha, a.data(), &lda, b.data(), &ldb, &beta, c.data(), &ldc);
    }
  };



// /---------------------------------------------Complex-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_her2k_, tag::cpu_
                            , (UPLO)(TRANS)(ALPHA)(A)(SA)(B)(SB)(BETA)(C)(SC)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<complex_<single_<ALPHA>>>)//alpha
                              ((container_<nt2::tag::table_, complex_<single_<A>>, SA >)) //a
                              ((container_<nt2::tag::table_, complex_<single_<B>>, SB >)) //b
                              (scalar_<single_<BETA>>)// beta
                              ((container_<nt2::tag::table_, complex_<single_<C>>, SC >)) //c
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const TRANS& trans
                                     , const ALPHA& alpha
                                     , const A& a
                                     , const B& b
                                     , const BETA& beta
                                     , C& c
                                     ) const
    {
      nt2_la_int n = height(c);  //((uplo == 'N')||(uplo == 'n')) ? height(b) : width(b);
      nt2_la_int k = ((trans == 'N')||(trans == 'n')) ?  width(a) : height(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldb = b.leading_size();
      nt2_la_int ldc = c.leading_size();
      NT2_F77NAME(cher2k) (&uplo, &trans, &n, &k, &alpha, a.data(), &lda, b.data(), &ldb, &beta, c.data(), &ldc);
    }
  };

// /---------------------------------------------Complex-double------------------------------------------------//
  BOOST_DISPATCH_IMPLEMENT  ( blas_her2k_, tag::cpu_
                            , (UPLO)(TRANS)(ALPHA)(A)(SA)(B)(SB)(BETA)(C)(SC)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<complex_<double_<ALPHA>>>)//alpha
                              ((container_<nt2::tag::table_, complex_<double_<A>>, SA >)) //a
                              ((container_<nt2::tag::table_, complex_<double_<B>>, SB >)) //b
                              (scalar_<double_<BETA>>)// beta
                              ((container_<nt2::tag::table_, complex_<double_<C>>, SC >)) //c
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const TRANS& trans
                                     , const ALPHA& alpha
                                     , const A& a
                                     , const B& b
                                     , const BETA& beta
                                     , C& c
                                     ) const
    {
      nt2_la_int n = height(c);  //((uplo == 'N')||(uplo == 'n')) ? height(b) : width(b);
      nt2_la_int k = ((trans == 'N')||(trans == 'n')) ?  width(a) : height(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldb = b.leading_size();
      nt2_la_int ldc = c.leading_size();
      NT2_F77NAME(zher2k) (&uplo, &trans, &n, &k, &alpha, a.data(), &lda, b.data(), &ldb, &beta, c.data(), &ldc);
    }
  };


} }

#endif
