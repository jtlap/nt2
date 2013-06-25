//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef FACTORIZATION_REFERENCE_DETAILS_HPP_INCLUDED
#define FACTORIZATION_REFERENCE_DETAILS_HPP_INCLUDED

extern "C"
{
  void NT2_F77NAME(dgetrf)( const nt2_la_int* m , const nt2_la_int* n
                          , double* a           , const nt2_la_int* lda
                          , nt2_la_int* ipiv    , nt2_la_int* info
                          );

  void NT2_F77NAME(sgetrf)( const nt2_la_int* m , const nt2_la_int* n
                          , float* a            , const nt2_la_int* lda
                          , nt2_la_int* ipiv    , nt2_la_int* info
                          );

  void NT2_F77NAME(dgeqp3)( const nt2_la_int* m  , const nt2_la_int* n
                          , double* a            , const nt2_la_int* lda
                          , nt2_la_int* jpvt     , double* tau
                          , double* work         , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(sgeqp3)( const nt2_la_int* m  , const nt2_la_int* n
                          , float* a             , const nt2_la_int* lda
                          , nt2_la_int* jpvt     , float* tau
                          , float* work          , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(dgeqrf)( const nt2_la_int* m     , const nt2_la_int* n
                          , double* a               , const nt2_la_int* lda
                          , double* tau             , double* work
                          , const nt2_la_int* lwork , nt2_la_int* info
                          );

  void NT2_F77NAME(sgeqrf)( const nt2_la_int* m     , const nt2_la_int* n
                          , float* a                , const nt2_la_int* lda
                          , float* tau              , float* work
                          , const nt2_la_int* lwork , nt2_la_int* info
                          );

  void NT2_F77NAME(dorgqr)( const nt2_la_int* m     , const nt2_la_int* n
                          , const nt2_la_int* k     , double* a
                          , const nt2_la_int* lda   , const double* tau
                          , double* work            , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(sorgqr)( const nt2_la_int* m     , const nt2_la_int* n
                          , const nt2_la_int* k     , float* a
                          , const nt2_la_int* lda   , const float* tau
                          , float* work             , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(dormqr)( const char* side        , const char* trans
                          , const nt2_la_int* m     , const nt2_la_int* n
                          , const nt2_la_int* k     , const double* a
                          , const nt2_la_int* lda   , const double* tau
                          , double* c               , const nt2_la_int* ldc
                          , double* work            , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(sormqr)( const char* side        , const char* trans
                          , const nt2_la_int* m     , const nt2_la_int* n
                          , const nt2_la_int* k     , const float* a
                          , const nt2_la_int* lda   , const float* tau
                          , float* c                , const nt2_la_int* ldc
                          , float* work             , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );
}

#endif
