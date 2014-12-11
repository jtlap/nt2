//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_BLAS3_SYRK_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_BLAS3_SYRK_HPP_INCLUDED

#include <nt2/linalg/functions/blas_syrk.hpp>
#include <nt2/linalg/details/blas/blas3.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/sdk/memory/container.hpp>

namespace nt2 { namespace ext
{

// /---------------------------------------------Real-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_syrk_, tag::cpu_
                            , (UPLO)(TRANS)(ALPHA)(A)(SA)(BETA)(C)(SC)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<single_<ALPHA>>)//alpha
                              ((container_<nt2::tag::table_,  single_<A>, SA >)) //a
                              (scalar_<single_<BETA>>)// beta
                              ((container_<nt2::tag::table_,  single_<C>, SC >)) //c
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const TRANS& trans
                                     , const ALPHA& alpha
                                     , const A& a
                                     , const BETA beta
                                     , C& c
                                     ) const
    {
      nt2_la_int n = height(c);  //((uplo == 'N')||(uplo == 'n')) ? height(b) : width(b);
      nt2_la_int k = ((trans == 'N')||(trans == 'n')) ?  width(a) : height(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldc = c.leading_size();
      NT2_F77NAME(ssyrk) (&uplo, &trans, &n, &k, &alpha, a.raw(), &lda, &beta, c.raw(), &ldc);
    }
  };

// /---------------------------------------------Real-double------------------------------------------------//
  BOOST_DISPATCH_IMPLEMENT  ( blas_syrk_, tag::cpu_
                            , (UPLO)(TRANS)(ALPHA)(A)(SA)(BETA)(C)(SC)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<double_<ALPHA>>)//alpha
                              ((container_<nt2::tag::table_,  double_<A>, SA >)) //a
                              (scalar_<double_<BETA>>)// beta
                              ((container_<nt2::tag::table_,  double_<C>, SC >)) //c
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const TRANS& trans
                                     , const ALPHA& alpha
                                     , const A& a
                                     , const BETA& beta
                                     , C& c
                                     ) const
    {
      nt2_la_int n = height(c);  //((uplo == 'N')||(uplo == 'n')) ? height(b) : width(b);
      nt2_la_int k = ((trans == 'N')||(trans == 'n')) ?  width(a) : height(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldc = c.leading_size();
      NT2_F77NAME(dsyrk)  (&uplo, &trans, &n, &k, &alpha, a.raw(), &lda, &beta, c.raw(), &ldc);
    }
  };



// /---------------------------------------------Complex-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_syrk_, tag::cpu_
                            , (UPLO)(TRANS)(ALPHA)(A)(SA)(BETA)(C)(SC)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<complex_<single_<ALPHA>>>)//alpha
                              ((container_<nt2::tag::table_, complex_<single_<A>>, SA >)) //a
                              (scalar_<complex_<single_<BETA>>>)// beta
                              ((container_<nt2::tag::table_, complex_<single_<C>>, SC >)) //c
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const TRANS& trans
                                     , const ALPHA& alpha
                                     , const A& a
                                     , const BETA& beta
                                     , C& c
                                     ) const
    {
      nt2_la_int n = height(c);  //((uplo == 'N')||(uplo == 'n')) ? height(b) : width(b);
      nt2_la_int k = ((trans == 'N')||(trans == 'n')) ?  width(a) : height(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldc = c.leading_size();
      NT2_F77NAME(csyrk) (&uplo, &trans, &n, &k, &alpha, a.raw(), &lda, &beta, c.raw(), &ldc);
    }
  };

// /---------------------------------------------Complex-double------------------------------------------------//
  BOOST_DISPATCH_IMPLEMENT  ( blas_syrk_, tag::cpu_
                            , (UPLO)(TRANS)(ALPHA)(A)(SA)(BETA)(C)(SC)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<complex_<double_<ALPHA>>>)//alpha
                              ((container_<nt2::tag::table_, complex_<double_<A>>, SA >)) //a
                              (scalar_<complex_<double_<BETA>>>)// beta
                              ((container_<nt2::tag::table_, complex_<double_<C>>, SC >)) //c
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const TRANS& trans
                                     , const ALPHA& alpha
                                     , const A& a
                                     , const BETA& beta
                                     , C& c
                                     ) const
    {
      nt2_la_int n = height(c);  //((uplo == 'N')||(uplo == 'n')) ? height(b) : width(b);
      nt2_la_int k = ((trans == 'N')||(trans == 'n')) ?  width(a) : height(a);
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldc = c.leading_size();
      NT2_F77NAME(zsyrk) (&uplo, &trans, &n, &k, &alpha, a.raw(), &lda, &beta, c.raw(), &ldc);
    }
  };


} }

#endif
