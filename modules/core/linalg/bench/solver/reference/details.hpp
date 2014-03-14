//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef SOLVER_REFERENCE_DETAILS_HPP_INCLUDED
#define SOLVER_REFERENCE_DETAILS_HPP_INCLUDED

extern "C"
{
  void NT2_F77NAME(dgesv)( const nt2_la_int* n, const nt2_la_int* nrhs
                         , double* a, const nt2_la_int* lda, nt2_la_int* ipiv
                         , double* b, const nt2_la_int* ldb, nt2_la_int* info
                         );

  void NT2_F77NAME(sgesv)( const nt2_la_int* n, const nt2_la_int* nrhs
                         , float* a, const nt2_la_int* lda, nt2_la_int* ipiv
                         , float* b, const nt2_la_int* ldb, nt2_la_int* info
                         );

  void NT2_F77NAME(dgemv)(const char* trans, const nt2_la_int* M, const nt2_la_int* N,
                      const double* alpha, const double* A, const nt2_la_int* lda,
                      const double* dx, const nt2_la_int* incx, const double* beta,
                      double* dy, const nt2_la_int* incy
                        );

  void NT2_F77NAME(dgetrs)(const char* trans,const nt2_la_int* n,const nt2_la_int* nhrs
                          ,double* a, const nt2_la_int* lda, nt2_la_int* ipiv, double* b
                          ,const nt2_la_int* ldb, nt2_la_int* info
                          );

  void NT2_F77NAME(dgesvx)( const char* fact    , const char* trans
                          , const nt2_la_int* n , const nt2_la_int* nrhs
                          , const double* a     , const nt2_la_int* lda
                          , double* af          , const nt2_la_int* ldaf
                          , nt2_la_int* ipiv    , const char* equed
                          , double* r           , double* c
                          , const double* b     , const nt2_la_int* ldb
                          , double* x           , const nt2_la_int* ldx
                          , double* rcond       , double* ferr
                          , double* berr        , double* work
                          , nt2_la_int* iwork   , nt2_la_int* info
                          );

  void NT2_F77NAME(sgesvx)( const char* fact    , const char* trans
                          , const nt2_la_int* n , const nt2_la_int* nrhs
                          , const float* a      , const nt2_la_int* lda
                          , float* af           , const nt2_la_int* ldaf
                          , nt2_la_int* ipiv    , const char* equed
                          , float* r            , float* c
                          , const float* b      , const nt2_la_int* ldb
                          , float* x            , const nt2_la_int* ldx
                          , float* rcond        , float* ferr
                          , float* berr         , float* work
                          , nt2_la_int* iwork   , nt2_la_int* info
                          );

}

#endif
