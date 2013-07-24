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

#include <nt2/linalg/functions/refine.hpp>
#include <nt2/linalg/details/magma_buffer.hpp>
#include <nt2/sdk/magma/magma.hpp>

#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/core/container/table/category.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

#include <nt2/table.hpp>

#include <magma.h>
#include <cublas.h>


namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dgerfs_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(site)
                            , ((expr_ < details::magma_buffer_< double_<A0>, S0 >     //A
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < details::magma_buffer_< double_<A1>, S1 >     //B
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < details::magma_buffer_< double_<A2>, S2 >     //X
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                            )
  {

magma_dgerfs_gpu(char trans, magma_int_t N, magma_int_t NRHS,
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



cublasStatus_t stat;



        /*
           Check The Parameters.
           */
        *info = *iter = 0 ;
        if ( N <0)
                *info = -1;
        else if(NRHS<0)
                *info =-2;
        else if(ldda < max(1,N))
                *info =-4;
        else if( lddb < max(1,N))
                *info =-8;
        else if( lddx < max(1,N))
                *info =-10;

        if (*info != 0) {
                magma_xerbla( __func__, -(*info) );
                return *info;
        }

        if( N == 0 || NRHS == 0 )
                return *info;

        eps  = lapackf77_dlamch("Epsilon");




    Anrm = magmablas_dlange('I', N, N, dA, ldda, dworkd );




    cte  = Anrm * eps * pow((double)N,0.5) * BWDMAX;

    if(*info !=0){
        *iter = -2 ;
        printf("magmablas_dlag2s\n");
        goto L40;
    }

    if(info[0] !=0){
        *iter = -3 ;
        goto L40;
    }

    magmablas_dlacpy(MagmaUpperLower, N, NRHS, dB, lddb, dworkd, N);


    /* TODO: update optimisation from gemv_MLU into classic gemv */
    if ( NRHS == 1 )
        magma_dgemv( trans, N, N, c_neg_one, dA, ldda, dX, 1, c_one, dworkd, 1);
    else
        magma_dgemm( trans, MagmaNoTrans, N, NRHS, N, c_neg_one, dA, ldda, dX, lddx,
c_one, dworkd, N);

    for(i=0;i<NRHS;i++)
    {
        j = magma_idamax( N, dX+i*lddx, 1) ;
#ifdef ERROR_H
        printf(" error defined\n");
#endif
        magma_dgetmatrix( 1, 1, dX+i*lddx+j-1, 1, &Xnrmv, 1 );

        Xnrm = lapackf77_dlange( "F", &ione, &ione, &Xnrmv, &ione, NULL );

        j = magma_idamax ( N, dworkd+i*N, 1 );
        magma_dgetmatrix( 1, 1, dworkd+i*N+j-1, 1, &Rnrmv, 1 );
        Rnrm = lapackf77_dlange( "F", &ione, &ione, &Rnrmv, &ione, NULL );



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
        /*

        */
        magma_dgetrs_gpu(trans, N, NRHS, dAF, lddaf, IPIV, dworkd, lddb,  info );
        if(info[0] != 0){
            *iter = -3 ;
            goto L40;
        }
        /* */
        for(i=0;i<NRHS;i++){
            magmablas_daxpycp(dworkd+i*N, dX+i*lddx, N, dB+i*lddb);
        }

        //magmablas_dlacpy(MagmaUpperLower, N, NRHS, dB, lddb, dworkd, N);
        if( NRHS == 1 )
            /* TODO: update optimisation from gemv_MLU into classic gemv */
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
            Xnrm = lapackf77_dlange( "F", &ione, &ione, &Xnrmv, &ione, NULL );

            j = magma_idamax ( N, dworkd+i*N, 1 );
            magma_dgetmatrix( 1, 1, dworkd+i*N+j-1, 1, &Rnrmv, 1 );
            Rnrm = lapackf77_dlange( "F", &ione, &ione, &Rnrmv, &ione, NULL );

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
    /*
      Single-precision iterative refinement failed to converge to a
      satisfactory solution, so we resort to double precision.
    */
    if( *info != 0 ){
        return *info;
    }

    return *info;
}


     }
  };

} }

#endif

#endif
