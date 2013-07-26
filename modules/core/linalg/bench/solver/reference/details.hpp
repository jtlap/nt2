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

}

#endif
