//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================


/*
  FLOP for LU from LAPACK Working Note 41
*/

#define FLOPS_DGETRF(__m, __n) (     FMULS_GETRF((double)(__m), (double)(__n)) +       FADDS_GETRF((double)(__m), (double)(__n)) )

#define FMULS_GETRF(__m, __n) ( ((__m) < (__n)) ? (0.5 * (__m) * ((__m) * ((__n) - (1./3.) * (__m) - 1. ) + (__n)) + (2. / 3.) * (__m))   \
                                :                 (0.5 * (__n) * ((__n) * ((__m) - (1./3.) * (__n) - 1. ) + (__m)) + (2. / 3.) * (__n)) ) \
/**/

#define FADDS_GETRF(__m, __n) ( ((__m) < (__n)) ? (0.5 * (__m) * ((__m) * ((__n) - (1./3.) * (__m)      ) - (__n)) + (1. / 6.) * (__m))   \
                                :                 (0.5 * (__n) * ((__n) * ((__m) - (1./3.) * (__n)      ) - (__m)) + (1. / 6.) * (__n)) ) \



/**/
#define FLOPS_DGETRS(__n, __nrhs) (     FMULS_GETRS((double)(__n), (double)(__nrhs)) +       FADDS_GETRS((double)(__n), (double)(__nrhs)) )

#define FMULS_GETRS(__n, __nrhs) ((__nrhs) * (__n) *  (__n)      )
#define FADDS_GETRS(__n, __nrhs) ((__nrhs) * (__n) * ((__n) - 1 ))

/**/
#define FLOPS_DGEQRF(__m, __n) (     FMULS_GEQRF((double)(__m), (double)(__n)) +       FADDS_GEQRF((double)(__m), (double)(__n)) )

/**/

#define FMULS_GEQRF(__m, __n) (((__m) > (__n)) ? ((__n) * ((__n) * (  0.5-(1./3.) * (__n) + (__m)) +    (__m) + 23. / 6.)) \
                               :                 ((__m) * ((__m) * ( -0.5-(1./3.) * (__m) + (__n)) + 2.*(__n) + 23. / 6.)) )
#define FADDS_GEQRF(__m, __n) (((__m) > (__n)) ? ((__n) * ((__n) * (  0.5-(1./3.) * (__n) + (__m))            +  5. / 6.)) \
                               :                 ((__m) * ((__m) * ( -0.5-(1./3.) * (__m) + (__n)) +    (__n) +  5. / 6.)) )

/**/

#define FLOPS_DORGQR(__m, __n, __k) (     FMULS_UNGQR((double)(__m), (double)(__n), (double)(__k)) +       FADDS_UNGQR((double)(__m), (double)(__n), (double)(__k)) )

/**/

#define FMULS_UNGQR(__m, __n, __k) ((__k) * (2.* (__m) * (__n) +    2. * (__n) - 5./3. + (__k) * ( 2./3. * (__k) - ((__m) + (__n)) - 1.)))

#define FADDS_UNGQR(__m, __n, __k) ((__k) * (2.* (__m) * (__n) + (__n) - (__m) + 1./3. + (__k) * ( 2./3. * (__k) - ((__m) + (__n))     )))

/**/

#define FLOPS_DORMQR(__m, __n, __k) (FMULS_UNMQR((double)(__m), (double)(__n), (double)(__k)  +       FADDS_UNMQR((double)(__m), (double)(__n), (double)(__k)) ))

/**/

#define FMULS_UNMQR(__m, __n, __k)  (2.*(__n)*(__m)*(__k) - (__n)*(__k)*(__k) + 2.*(__n)*(__k))

#define FADDS_UNMQR(__m, __n, __k)  (2.*(__n)*(__m)*(__k) - (__n)*(__k)*(__k) + (__n)*(__k))

/**/


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

  void NT2_F77NAME(dgesv)( const nt2_la_int* n, const nt2_la_int* nrhs
                         , double* a, const nt2_la_int* lda, nt2_la_int* ipiv
                         , double* b, const nt2_la_int* ldb, nt2_la_int* info
                         );

  void NT2_F77NAME(sgesv)( const nt2_la_int* n, const nt2_la_int* nrhs
                         , float* a, const nt2_la_int* lda, nt2_la_int* ipiv
                         , float* b, const nt2_la_int* ldb, nt2_la_int* info
                         );
}



