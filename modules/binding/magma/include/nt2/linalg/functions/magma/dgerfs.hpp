//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MAGMA_DGERFS_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MAGMA_DGERFS_HPP_INCLUDED

#if defined(NT2_USE_MAGMA)

#include <nt2/sdk/magma/magma.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/magma_buffer.hpp>
#include <nt2/linalg/details/lapack/lange.hpp>
#include <nt2/core/container/table/kind.hpp>
#include <nt2/include/functions/pow.hpp>
#include <magma.h>

#include <nt2/core/container/table/table.hpp>

#define BWDMAX 1.0
#define ITERMAX 5

magma_int_t
dgerfs_gpu(magma_trans_t trans, magma_int_t N, magma_int_t NRHS,
                double *dA, magma_int_t ldda,
                double *dAF, magma_int_t lddaf,
                magma_int_t *IPIV,
                double *dB, magma_int_t lddb,
                double *dX, magma_int_t lddx,
                double *dworkd,
                magma_int_t *iter, magma_int_t *info)
{

double c_neg_one = MAGMA_D_NEG_ONE;
double c_one     = MAGMA_D_ONE;
magma_int_t     ione  = 1;
double          cte, eps;
double Xnrmv, Rnrmv;
double          Anrm, Xnrm, Rnrm;
magma_int_t     i, j, iiter;

/*
 Check The Parameters.
*/
*info = *iter = 0 ;
if ( N <0)
    *info = -1;
else if(NRHS<0)
    *info =-2;
else if(ldda < std::max(1,N))
    *info =-4;
else if( lddb < std::max(1,N))
    *info =-8;
else if( lddx < std::max(1,N))
    *info =-10;

if (*info != 0) {
    magma_xerbla( __func__, -(*info) );
    return *info;
}

if( N == 0 || NRHS == 0 )
    return *info;

eps  = boost::simd::Eps<double>();

Anrm = magmablas_dlange(MagmaInfNorm, N, N, dA, ldda, dworkd );

cte  = Anrm * eps * nt2::pow((double)N,0.5) * BWDMAX;


if(*info !=0){
    *iter = -2 ;
    goto L40;
}

if(info[0] !=0){
    *iter = -3 ;
    goto L40;
}

magmablas_dlacpy(MagmaUpperLower, N, NRHS, dB, lddb, dworkd, N);


if ( NRHS == 1 )
    magma_dgemv( trans, N, N, c_neg_one, dA, ldda, dX, 1, c_one, dworkd, 1);

else
    magma_dgemm( trans, MagmaNoTrans, N, NRHS, N, c_neg_one, dA, ldda, dX, lddx,
c_one, dworkd, N);

    for(i=0;i<NRHS;i++)
    {
        j = magma_idamax( N, dX+i*lddx, 1) ;

        magma_dgetmatrix( 1, 1, dX+i*lddx+j-1, 1, &Xnrmv, 1 );

        Xnrm = NT2_F77NAME(dlange) ( "F", &ione, &ione, &Xnrmv, &ione, NULL );

        j = magma_idamax ( N, dworkd+i*N, 1 );
        magma_dgetmatrix( 1, 1, dworkd+i*N+j-1, 1, &Rnrmv, 1 );
        Rnrm = NT2_F77NAME(dlange) ( "F", &ione, &ione, &Rnrmv, &ione, NULL );

        if( Rnrm >  (Xnrm*cte) ){
            goto L10;
        }
    }

    *iter = 0;
    return *info;
  L10:
    ;
    for(iiter=1;iiter<ITERMAX;)
    {
        *info = 0 ;

        magma_dgetrs_gpu(trans, N, NRHS, dAF, lddaf, IPIV, dworkd, lddb,  info );
        if(info[0] != 0){
            *iter = -3 ;
            goto L40;
        }

        for(i=0;i<NRHS;i++){
#if MAGMA_VERSION_MAJOR <= 1 && MAGMA_VERSION_MINOR < 4
            magmablas_daxpycp(dworkd+i*N, dX+i*lddx, N, dB+i*lddb);
#else
            magmablas_daxpycp(N, dworkd+i*N, dX+i*lddx, dB+i*lddb);
#endif
        }

        //magmablas_dlacpy(MagmaUpperLower, N, NRHS, dB, lddb, dworkd, N);
        if( NRHS == 1 )

            magma_dgemv( trans, N, N, c_neg_one, dA, ldda, dX, 1, c_one, dworkd, 1);
        else
            magma_dgemm( trans, MagmaNoTrans, N, NRHS, N, c_neg_one, dA, ldda, dX,
lddx, c_one, dworkd, N);

        /*
          Check whether the NRHS normwise backward errors satisfy the
          stopping criterion. If yes, set ITER=IITER>0 and return.
        */
        for(i=0;i<NRHS;i++)
        {
            j = magma_idamax( N, dX+i*lddx, 1) ;
            magma_dgetmatrix( 1, 1, dX+i*lddx+j-1, 1, &Xnrmv, 1 );
            Xnrm = NT2_F77NAME(dlange)( "F", &ione, &ione, &Xnrmv, &ione, NULL );

            j = magma_idamax ( N, dworkd+i*N, 1 );
            magma_dgetmatrix( 1, 1, dworkd+i*N+j-1, 1, &Rnrmv, 1 );
            Rnrm = NT2_F77NAME(dlange)( "F", &ione, &ione, &Rnrmv, &ione, NULL );

            if( Rnrm >  Xnrm *cte ){
                goto L20;
            }
        }
        /*
          If we are here, the NRHS normwise backward errors satisfy the
          stopping criterion, we are good to exit.
        */

        *iter = iiter ;
        return *info;
      L20:
        iiter++ ;
    }
    /*
      If we are at this place of the code, this is because we have
      performed ITER=ITERMAX iterations and never satisified the
      stopping criterion, set up the ITER flag accordingly and follow up
      on double precision routine.
    */
    *iter = -ITERMAX - 1 ;

  L40:
    if( *info != 0 ){
        return *info;
    }

    return *info;
}



 magma_int_t
sgerfs_gpu(magma_trans_t trans, magma_int_t N, magma_int_t NRHS,
                float *dA, magma_int_t ldda,
                float *dAF, magma_int_t lddaf,
                magma_int_t *IPIV,
                float *dB, magma_int_t lddb,
                float *dX, magma_int_t lddx,
                float *dworks,
                magma_int_t *iter, magma_int_t *info)
{

nt2::details::magma_buffer<double> dworkd(N,1);
nt2::details::magma_buffer<double> dXd(N,NRHS);
nt2::details::magma_buffer<double> dBd(N,NRHS);

float c_neg_one = MAGMA_D_NEG_ONE;
float c_one     = MAGMA_D_ONE;
magma_int_t     ione  = 1;
float          cte, eps;
float Xnrmv, Rnrmv;
float          Anrm, Xnrm, Rnrm;
magma_int_t     i, j, iiter,info1;

/*
 Check The Parameters.
*/
*info = *iter = 0 ;
if ( N <0)
    *info = -1;
else if(NRHS<0)
    *info =-2;
else if(ldda < std::max(1,N))
    *info =-4;
else if( lddb < std::max(1,N))
    *info =-8;
else if( lddx < std::max(1,N))
    *info =-10;

if (*info != 0) {
    magma_xerbla( __func__, -(*info) );
    return *info;
}

if( N == 0 || NRHS == 0 )
    return *info;

eps  = boost::simd::Eps<float>();

Anrm = magmablas_slange(MagmaInfNorm, N, N, dA, ldda, dworks );

cte  = Anrm * eps * nt2::pow((float)N,(float)0.5) * BWDMAX;

if(*info !=0){
    *iter = -2 ;
    goto L40;
}

if(info[0] !=0){
    *iter = -3 ;
    goto L40;
}

magmablas_slacpy(MagmaUpperLower, N, NRHS, dB, lddb, dworks, N);

if ( NRHS == 1 )
    magma_sgemv( trans, N, N, c_neg_one, dA, ldda, dX, 1, c_one, dworks, 1);
else
    magma_sgemm( trans, MagmaNoTrans, N, NRHS, N, c_neg_one, dA, ldda, dX, lddx,
c_one, dworks, N);

    for(i=0;i<NRHS;i++)
    {
        j = magma_isamax( N, dX+i*lddx, 1) ;

        magma_sgetmatrix( 1, 1, dX+i*lddx+j-1, 1, &Xnrmv, 1 );

        Xnrm = NT2_F77NAME(slange) ( "F", &ione, &ione, &Xnrmv, &ione, NULL );

        j = magma_isamax ( N, dworks+i*N, 1 );
        magma_sgetmatrix( 1, 1, dworks+i*N+j-1, 1, &Rnrmv, 1 );
        Rnrm = NT2_F77NAME(slange) ( "F", &ione, &ione, &Rnrmv, &ione, NULL );

        if( Rnrm >  (Xnrm*cte) ){
            goto L10;
        }
    }

    *iter = 0;
    return *info;
  L10:
    ;

    for(iiter=1;iiter<ITERMAX;)
    {
        *info = 0 ;

        magma_sgetrs_gpu(trans, N, NRHS, dAF, lddaf, IPIV, dworks, lddb,  info );
        if(info[0] != 0){
            *iter = -3 ;
            goto L40;
        }
        // float -> double?
        for(i=0;i<NRHS;i++){
            magmablas_slag2d(N,NRHS,dX,N,dXd.data(),N,&info1);
            magmablas_slag2d(N,NRHS,dB,N,dBd.data(),N,&info1);
            magmablas_slag2d(N,c_one,dworks,N,dworkd.data(),N,&info1);

#if MAGMA_VERSION_MAJOR <= 1 && MAGMA_VERSION_MINOR < 4
            magmablas_daxpycp(dworkd.data()+i*N, dXd.data()+i*lddx, N, dBd.data()+i*lddb);
#else
            magmablas_daxpycp(N, dworkd.data()+i*N, dXd.data()+i*lddx, dBd.data()+i*lddb);
#endif

            magmablas_dlag2s(N,NRHS,dXd.data(),N,dX,N,&info1);
            magmablas_dlag2s(N,NRHS,dBd.data(),N,dB,N,&info1);
            magmablas_dlag2s(N,c_one,dworkd.data(),N,dworks,N,&info1);
        }

        //magmablas_dlacpy(MagmaUpperLower, N, NRHS, dB, lddb, dworkd, N);
        if( NRHS == 1 )

            magma_sgemv( trans, N, N, c_neg_one, dA, ldda, dX, 1, c_one, dworks, 1);
        else
            magma_sgemm( trans, MagmaNoTrans, N, NRHS, N, c_neg_one, dA, ldda, dX,
lddx, c_one, dworks, N);

        /*
          Check whether the NRHS normwise backward errors satisfy the
          stopping criterion. If yes, set ITER=IITER>0 and return.
        */
        for(i=0;i<NRHS;i++)
        {
            j = magma_isamax( N, dX+i*lddx, 1) ;
            magma_sgetmatrix( 1, 1, dX+i*lddx+j-1, 1, &Xnrmv, 1 );
            Xnrm = NT2_F77NAME(slange)( "F", &ione, &ione, &Xnrmv, &ione, NULL );

            j = magma_isamax ( N, dworks+i*N, 1 );
            magma_sgetmatrix( 1, 1, dworks+i*N+j-1, 1, &Rnrmv, 1 );
            Rnrm = NT2_F77NAME(slange)( "F", &ione, &ione, &Rnrmv, &ione, NULL );

            if( Rnrm >  Xnrm *cte ){
                goto L20;
            }
        }
        /*
          If we are here, the NRHS normwise backward errors satisfy the
          stopping criterion, we are good to exit.
        */

        *iter = iiter ;
        return *info;
      L20:
        iiter++ ;
    }
    /*
      If we are at this place of the code, this is because we have
      performed ITER=ITERMAX iterations and never satisified the
      stopping criterion, set up the ITER flag accordingly and follow up
      on double precision routine.
    */
    *iter = -ITERMAX - 1 ;

  L40:
    if( *info != 0 ){
        return *info;
    }

    return *info;
}

//---------------------------------------Complex------------------------------------//

magma_int_t
zgerfs_gpu(magma_trans_t trans, magma_int_t N, magma_int_t NRHS,
                cuDoubleComplex *dA, magma_int_t ldda,
                cuDoubleComplex *dAF, magma_int_t lddaf,
                magma_int_t *IPIV,
                cuDoubleComplex *dB, magma_int_t lddb,
                cuDoubleComplex *dX, magma_int_t lddx,
                cuDoubleComplex *dworkd,
                magma_int_t *iter, magma_int_t *info)
{

cuDoubleComplex c_neg_one = MAGMA_Z_NEG_ONE;
cuDoubleComplex c_one     = MAGMA_Z_ONE;
magma_int_t     ione  = 1;
double          cte, eps;
cuDoubleComplex Xnrmv, Rnrmv;
double          Anrm, Xnrm, Rnrm;
magma_int_t     i, j, iiter;

/*
 Check The Parameters.
*/
*info = *iter = 0 ;
if ( N <0)
    *info = -1;
else if(NRHS<0)
    *info =-2;
else if(ldda < std::max(1,N))
    *info =-4;
else if( lddb < std::max(1,N))
    *info =-8;
else if( lddx < std::max(1,N))
    *info =-10;

if (*info != 0) {
    magma_xerbla( __func__, -(*info) );
    return *info;
}

if( N == 0 || NRHS == 0 )
    return *info;

eps  = boost::simd::Eps<double>();

Anrm = magmablas_zlange(MagmaInfNorm, N, N, dA, ldda, (double*)dworkd );

cte  = Anrm * eps * nt2::pow((double)N,0.5) * BWDMAX;


if(*info !=0){
    *iter = -2 ;
    goto L40;
}

if(info[0] !=0){
    *iter = -3 ;
    goto L40;
}

magmablas_zlacpy(MagmaUpperLower, N, NRHS, dB, lddb, dworkd, N);


if ( NRHS == 1 )
    magma_zgemv( trans, N, N, c_neg_one, dA, ldda, dX, 1, c_one, dworkd, 1);

else
    magma_zgemm( trans, MagmaNoTrans, N, NRHS, N, c_neg_one, dA, ldda, dX, lddx,
c_one, dworkd, N);

    for(i=0;i<NRHS;i++)
    {
        j = magma_izamax( N, dX+i*lddx, 1) ;

        magma_zgetmatrix( 1, 1, dX+i*lddx+j-1, 1, &Xnrmv, 1 );

        Xnrm = NT2_F77NAME(zlange) ( "F", &ione, &ione, &Xnrmv, &ione, NULL );

        j = magma_izamax ( N, dworkd+i*N, 1 );
        magma_zgetmatrix( 1, 1, dworkd+i*N+j-1, 1, &Rnrmv, 1 );
        Rnrm = NT2_F77NAME(zlange) ( "F", &ione, &ione, &Rnrmv, &ione, NULL );

        if( Rnrm >  (Xnrm*cte) ){
            goto L10;
        }
    }

    *iter = 0;
    return *info;
  L10:
    ;
    for(iiter=1;iiter<ITERMAX;)
    {
        *info = 0 ;

        magma_zgetrs_gpu(trans, N, NRHS, dAF, lddaf, IPIV, dworkd, lddb,  info );
        if(info[0] != 0){
            *iter = -3 ;
            goto L40;
        }

        for(i=0;i<NRHS;i++){
#if MAGMA_VERSION_MAJOR <= 1 && MAGMA_VERSION_MINOR < 4
            magmablas_zaxpycp(dworkd+i*N, dX+i*lddx, N, dB+i*lddb);
#else
            magmablas_zaxpycp(N, dworkd+i*N, dX+i*lddx, dB+i*lddb);
#endif
        }

        //magmablas_dlacpy(MagmaUpperLower, N, NRHS, dB, lddb, dworkd, N);
        if( NRHS == 1 )

            magma_zgemv( trans, N, N, c_neg_one, dA, ldda, dX, 1, c_one, dworkd, 1);
        else
            magma_zgemm( trans, MagmaNoTrans, N, NRHS, N, c_neg_one, dA, ldda, dX,
lddx, c_one, dworkd, N);

        /*
          Check whether the NRHS normwise backward errors satisfy the
          stopping criterion. If yes, set ITER=IITER>0 and return.
        */
        for(i=0;i<NRHS;i++)
        {
            j = magma_izamax( N, dX+i*lddx, 1) ;
            magma_zgetmatrix( 1, 1, dX+i*lddx+j-1, 1, &Xnrmv, 1 );
            Xnrm = NT2_F77NAME(zlange)( "F", &ione, &ione, &Xnrmv, &ione, NULL );

            j = magma_izamax ( N, dworkd+i*N, 1 );
            magma_zgetmatrix( 1, 1, dworkd+i*N+j-1, 1, &Rnrmv, 1 );
            Rnrm = NT2_F77NAME(zlange)( "F", &ione, &ione, &Rnrmv, &ione, NULL );

            if( Rnrm >  Xnrm *cte ){
                goto L20;
            }
        }
        /*
          If we are here, the NRHS normwise backward errors satisfy the
          stopping criterion, we are good to exit.
        */

        *iter = iiter ;
        return *info;
      L20:
        iiter++ ;
    }
    /*
      If we are at this place of the code, this is because we have
      performed ITER=ITERMAX iterations and never satisified the
      stopping criterion, set up the ITER flag accordingly and follow up
      on double precision routine.
    */
    *iter = -ITERMAX - 1 ;

  L40:
    if( *info != 0 ){
        return *info;
    }

    return *info;
}



magma_int_t
cgerfs_gpu(magma_trans_t trans, magma_int_t N, magma_int_t NRHS,
                cuFloatComplex *dA, magma_int_t ldda,
                cuFloatComplex *dAF, magma_int_t lddaf,
                magma_int_t *IPIV,
                cuFloatComplex *dB, magma_int_t lddb,
                cuFloatComplex *dX, magma_int_t lddx,
                cuFloatComplex *dworkd,
                magma_int_t *iter, magma_int_t *info)
{

nt2::details::magma_buffer<std::complex<double> > dworkz(N,1);
nt2::details::magma_buffer<std::complex<double> > dXd(N,NRHS);
nt2::details::magma_buffer<std::complex<double> > dBd(N,NRHS);

cuFloatComplex c_neg_one = MAGMA_C_NEG_ONE;
cuFloatComplex c_one     = MAGMA_C_ONE;
float r_one     = MAGMA_D_ONE;
magma_int_t     ione  = 1;
double          cte, eps;
cuFloatComplex Xnrmv, Rnrmv;
double          Anrm, Xnrm, Rnrm;
magma_int_t     i, j, iiter,info1;

/*
 Check The Parameters.
*/
*info = *iter = 0 ;
if ( N <0)
    *info = -1;
else if(NRHS<0)
    *info =-2;
else if(ldda < std::max(1,N))
    *info =-4;
else if( lddb < std::max(1,N))
    *info =-8;
else if( lddx < std::max(1,N))
    *info =-10;

if (*info != 0) {
    magma_xerbla( __func__, -(*info) );
    return *info;
}

if( N == 0 || NRHS == 0 )
    return *info;

eps  = boost::simd::Eps<double>();

Anrm = magmablas_clange(MagmaInfNorm, N, N, dA, ldda, (float*)dworkd );

cte  = Anrm * eps * nt2::pow((double)N,0.5) * BWDMAX;


if(*info !=0){
    *iter = -2 ;
    goto L40;
}

if(info[0] !=0){
    *iter = -3 ;
    goto L40;
}

magmablas_clacpy(MagmaUpperLower, N, NRHS, dB, lddb, dworkd, N);


if ( NRHS == 1 )
    magma_cgemv( trans, N, N, c_neg_one, dA, ldda, dX, 1, c_one, dworkd, 1);

else
    magma_cgemm( trans, MagmaNoTrans, N, NRHS, N, c_neg_one, dA, ldda, dX, lddx,
c_one, dworkd, N);

    for(i=0;i<NRHS;i++)
    {
        j = magma_icamax( N, dX+i*lddx, 1) ;

        magma_cgetmatrix( 1, 1, dX+i*lddx+j-1, 1, &Xnrmv, 1 );

        Xnrm = NT2_F77NAME(clange) ( "F", &ione, &ione, &Xnrmv, &ione, NULL );

        j = magma_icamax ( N, dworkd+i*N, 1 );
        magma_cgetmatrix( 1, 1, dworkd+i*N+j-1, 1, &Rnrmv, 1 );
        Rnrm = NT2_F77NAME(clange) ( "F", &ione, &ione, &Rnrmv, &ione, NULL );

        if( Rnrm >  (Xnrm*cte) ){
            goto L10;
        }
    }

    *iter = 0;
    return *info;
  L10:
    ;
    for(iiter=1;iiter<ITERMAX;)
    {
        *info = 0 ;

        magma_cgetrs_gpu(trans, N, NRHS, dAF, lddaf, IPIV, dworkd, lddb,  info );
        if(info[0] != 0){
            *iter = -3 ;
            goto L40;
        }
        //float -> double ?
        for(i=0;i<NRHS;i++){
            magmablas_clag2z(N,NRHS,dX,N,(cuDoubleComplex*)dXd.data(),N,&info1);
            magmablas_clag2z(N,NRHS,dB,N,(cuDoubleComplex*)dBd.data(),N,&info1);
            magmablas_clag2z(N,r_one,dworkd,N,(cuDoubleComplex*)dworkz.data(),N,&info1);

#if MAGMA_VERSION_MAJOR <= 1 && MAGMA_VERSION_MINOR < 4
            magmablas_zaxpycp( (cuDoubleComplex*)dworkz.data()+i*N
                             , (cuDoubleComplex*)dXd.data()+i*lddx
                             , N
                             , (cuDoubleComplex*)dBd.data()+i*lddb
                             );
#else
            magmablas_zaxpycp( N
                             , (cuDoubleComplex*)dworkz.data()+i*N
                             , (cuDoubleComplex*)dXd.data()+i*lddx
                             , (cuDoubleComplex*)dBd.data()+i*lddb
                             );
#endif

            magmablas_zlag2c(N,NRHS,(cuDoubleComplex*)dXd.data(),N,dX,N,&info1);
            magmablas_zlag2c(N,NRHS,(cuDoubleComplex*)dBd.data(),N,dB,N,&info1);
            magmablas_zlag2c(N,r_one,(cuDoubleComplex*)dworkz.data(),N,dworkd,N,&info1);
        }

        //magmablas_dlacpy(MagmaUpperLower, N, NRHS, dB, lddb, dworkd, N);
        if( NRHS == 1 )

            magma_cgemv( trans, N, N, c_neg_one, dA, ldda, dX, 1, c_one, dworkd, 1);
        else
            magma_cgemm( trans, MagmaNoTrans, N, NRHS, N, c_neg_one, dA, ldda, dX,
lddx, c_one, dworkd, N);

        /*
          Check whether the NRHS normwise backward errors satisfy the
          stopping criterion. If yes, set ITER=IITER>0 and return.
        */
        for(i=0;i<NRHS;i++)
        {
            j = magma_icamax( N, dX+i*lddx, 1) ;
            magma_cgetmatrix( 1, 1, dX+i*lddx+j-1, 1, &Xnrmv, 1 );
            Xnrm = NT2_F77NAME(clange)("F", &ione, &ione, &Xnrmv, &ione, NULL );

            j = magma_icamax ( N, dworkd+i*N, 1 );
            magma_cgetmatrix( 1, 1, dworkd+i*N+j-1, 1, &Rnrmv, 1 );
            Rnrm = NT2_F77NAME(clange)("F", &ione, &ione, &Rnrmv, &ione, NULL );

            if( Rnrm >  Xnrm *cte ){
                goto L20;
            }
        }
        /*
          If we are here, the NRHS normwise backward errors satisfy the
          stopping criterion, we are good to exit.
        */

        *iter = iiter ;
        return *info;
      L20:
        iiter++ ;
    }
    /*
      If we are at this place of the code, this is because we have
      performed ITER=ITERMAX iterations and never satisified the
      stopping criterion, set up the ITER flag accordingly and follow up
      on double precision routine.
    */
    *iter = -ITERMAX - 1 ;

  L40:
    if( *info != 0 ){
        return *info;
    }

    return *info;
}
#endif

#endif
