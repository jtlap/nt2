//==============================================================================
//         Copyright 2015 - Jean-Thierry Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_DECLARE_HGEQZ_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_DECLARE_HGEQZ_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

/// Lapack declaration interface
///
/// excerpt from LAPACK documentation
// /// FOR ? s, d, C or Z
//  ?HGEQZ computes the eigenvalues of a  matrix pair (H,T),
// *  where H is an upper Hessenberg matrix and T is upper triangular,
// *  using the single-shift QZ method.
// *  Matrix pairs of this type are produced by the reduction to
// *  generalized upper Hessenberg form of a  matrix pair (A,B):
// *
// *     A = Q1*H*Z1**H,  B = Q1*T*Z1**H,
// *
// *  as computed by CGGHRD.
// *
// *  If JOB='S', then the Hessenberg-triangular pair (H,T) is
// *  also reduced to generalized Schur form,
// *
// *     H = Q*S*Z**H,  T = Q*P*Z**H,
// *
// *  where Q and Z are unitary matrices and S and P are upper triangular.
// *
// *  Optionally, the unitary matrix Q from the generalized Schur
// *  factorization may be postmultiplied into an input matrix Q1, and the
// *  unitary matrix Z may be postmultiplied into an input matrix Z1.
// *  If Q1 and Z1 are the unitary matrices from CGGHRD that reduced
// *  the matrix pair (A,B) to generalized Hessenberg form, then the output
// *  matrices Q1*Q and Z1*Z are the unitary factors from the generalized
// *  Schur factorization of (A,B):
// *
// *     A = (Q1*Q)*S*(Z1*Z)**H,  B = (Q1*Q)*P*(Z1*Z)**H.
// *
// *  To avoid overflow, eigenvalues of the matrix pair (H,T)
// *  (equivalently, of (A,B)) are computed as a pair of  values
// *  (alpha,beta).  If beta is nonzero, lambda = alpha / beta is an
// *  eigenvalue of the generalized nonsymmetric eigenvalue problem (GNEP)
// *     A*x = lambda*B*x
// *  and if alpha is nonzero, mu = beta / alpha is an eigenvalue of the
// *  alternate form of the GNEP
// *     mu*A*y = B*y.
// *  The values of alpha and beta for the i-th eigenvalue can be read
// *  directly from the generalized Schur form:  alpha = S(i,i),
// *  beta = P(i,i).
// *
// *  Ref: C.B. Moler & G.W. Stewart, "An Algorithm for Generalized Matrix
// *       Eigenvalue Problems", SIAM J. Numer. Anal., 10(1973),
// *       pp. 241--256.
// *
// *  Arguments
// *  =========
// *
// *  JOB     (input) CHARACTER*1
// *          = 'E': Compute eigenvalues only;
// *          = 'S': Computer eigenvalues and the Schur form.
// *
// *  COMPQ   (input) CHARACTER*1
// *          = 'N': Left Schur vectors (Q) are not computed;
// *          = 'I': Q is initialized to the unit matrix and the matrix Q
// *                 of left Schur vectors of (H,T) is returned;
// *          = 'V': Q must contain a unitary matrix Q1 on entry and
// *                 the product Q1*Q is returned.
// *
// *  COMPZ   (input) CHARACTER*1
// *          = 'N': Right Schur vectors (Z) are not computed;
// *          = 'I': Q is initialized to the unit matrix and the matrix Z
// *                 of right Schur vectors of (H,T) is returned;
// *          = 'V': Z must contain a unitary matrix Z1 on entry and
// *                 the product Z1*Z is returned.
// *
// *  N       (input) INTEGER
// *          The order of the matrices H, T, Q, and Z.  N >= 0.
// *
// *  ILO     (input) INTEGER
// *  IHI     (input) INTEGER
// *          ILO and IHI mark the rows and columns of H which are in
// *          Hessenberg form.  It is assumed that A is already upper
// *          triangular in rows and columns 1:ILO-1 and IHI+1:N.
// *          If N > 0, 1 <= ILO <= IHI <= N; if N = 0, ILO=1 and IHI=0.
// *
// *  H       (input/output)  array, dimension (LDH, N)
// *          On entry, the N-by-N upper Hessenberg matrix H.
// *          On exit, if JOB = 'S', H contains the upper triangular
// *          matrix S from the generalized Schur factorization.
// *          If JOB = 'E', the diagonal of H matches that of S, but
// *          the rest of H is unspecified.
// *
// *  LDH     (input) INTEGER
// *          The leading dimension of the array H.  LDH >= max( 1, N ).
// *
// *  T       (input/output)  array, dimension (LDT, N)
// *          On entry, the N-by-N upper triangular matrix T.
// *          On exit, if JOB = 'S', T contains the upper triangular
// *          matrix P from the generalized Schur factorization.
// *          If JOB = 'E', the diagonal of T matches that of P, but
// *          the rest of T is unspecified.
// *
// *  LDT     (input) INTEGER
// *          The leading dimension of the array T.  LDT >= max( 1, N ).
// *
// *  ALPHA   (output)  array, dimension (N)
// *          The  scalars alpha that define the eigenvalues of
// *          GNEP.  ALPHA(i) = S(i,i) in the generalized Schur
// *          factorization.
// *
// *  BETA    (output)  array, dimension (N)
// *          The real non-negative scalars beta that define the
// *          eigenvalues of GNEP.  BETA(i) = P(i,i) in the generalized
// *          Schur factorization.
// *
// *          Together, the quantities alpha = ALPHA(j) and beta = BETA(j)
// *          represent the j-th eigenvalue of the matrix pair (A,B), in
// *          one of the forms lambda = alpha/beta or mu = beta/alpha.
// *          Since either lambda or mu may overflow, they should not,
// *          in general, be computed.
// *
// *  Q       (input/output)  array, dimension (LDQ, N)
// *          On entry, if COMPZ = 'V', the unitary matrix Q1 used in the
// *          reduction of (A,B) to generalized Hessenberg form.
// *          On exit, if COMPZ = 'I', the unitary matrix of left Schur
// *          vectors of (H,T), and if COMPZ = 'V', the unitary matrix of
// *          left Schur vectors of (A,B).
// *          Not referenced if COMPZ = 'N'.
// *
// *  LDQ     (input) INTEGER
// *          The leading dimension of the array Q.  LDQ >= 1.
// *          If COMPQ='V' or 'I', then LDQ >= N.
// *
// *  Z       (input/output)  array, dimension (LDZ, N)
// *          On entry, if COMPZ = 'V', the unitary matrix Z1 used in the
// *          reduction of (A,B) to generalized Hessenberg form.
// *          On exit, if COMPZ = 'I', the unitary matrix of right Schur
// *          vectors of (H,T), and if COMPZ = 'V', the unitary matrix of
// *          right Schur vectors of (A,B).
// *          Not referenced if COMPZ = 'N'.
// *
// *  LDZ     (input) INTEGER
// *          The leading dimension of the array Z.  LDZ >= 1.
// *          If COMPZ='V' or 'I', then LDZ >= N.
// *
// *  WORK    (workspace/output)  array, dimension (MAX(1,LWORK))
// *          On exit, if INFO >= 0, WORK(1) returns the optimal LWORK.
// *
// *  LWORK   (input) INTEGER
// *          The dimension of the array WORK.  LWORK >= max(1,N).
// *
// *          If LWORK = -1, then a workspace query is assumed; the routine
// *          only calculates the optimal size of the WORK array, returns
// *          this value as the first entry of the WORK array, and no error
// *          message related to LWORK is issued by XERBLA.
// *
// *  RWORK   (workspace) REAL array, dimension (N)
// *
// *  INFO    (output) INTEGER
// *          = 0: successful exit
// *          < 0: if INFO = -i, the i-th argument had an illegal value
// *          = 1,...,N: the QZ iteration did not converge.  (H,T) is not
// *                     in Schur form, but ALPHA(i) and BETA(i),
// *                     i=INFO+1,...,N should be correct.
// *          = N+1,...,2*N: the shift calculation failed.  (H,T) is not
// *                     in Schur form, but ALPHA(i) and BETA(i),
// *                     i=INFO-N+1,...,N should be correct.
// *
extern "C"

{
  void NT2_F77NAME(dhgeqz)( const char* job,  const char* compq,   const char* compz
                          , const nt2_la_int* n , const nt2_la_int* ilo, const nt2_la_int* ihi
                          , double* h,  const nt2_la_int* ldh
                          , double* t,  const nt2_la_int* ldt
                          , double* alphar, double* alphai, double* beta
                          , double* q,  const nt2_la_int* ldq
                          , double* z,  const nt2_la_int* ldz
                          , double* w,  nt2_la_int* lw
                          , nt2_la_int* info
                          );
  void NT2_F77NAME(shgeqz)( const char* job, const char* compq,   const char* compz
                          , const nt2_la_int* n , const nt2_la_int* ilo, const nt2_la_int* ihi
                          , float* h,  const nt2_la_int* ldh
                          , float* t,  const nt2_la_int* ldt
                          , float* alphar, float* alphai, float* beta
                          , float* q,  const nt2_la_int* ldq
                          , float* z,  const nt2_la_int* ldz
                          , float* w,  nt2_la_int* lw
                          , nt2_la_int* info
                          );
  void NT2_F77NAME(chgeqz)( const char* job, const char* compq,   const char* compz
                          ,  const nt2_la_int* n , const nt2_la_int* ilo, const nt2_la_int* ihi
                          , nt2_la_complex* h,  const nt2_la_int* ldh
                          , nt2_la_complex* t,  const nt2_la_int* ldt
                          , nt2_la_complex* alpha, nt2_la_complex* beta
                          , nt2_la_complex* q,  const nt2_la_int* ldq
                          , nt2_la_complex* z,  const nt2_la_int* ldz
                          , nt2_la_complex* w,  nt2_la_int* lw, float* rw
                          , nt2_la_int* info
                          );
  void NT2_F77NAME(zhgeqz)( const char* job, const char* compq,   const char* compz
                          , const nt2_la_int* n , const nt2_la_int* ilo, const nt2_la_int* ihi
                          , nt2_la_complex* h,  const nt2_la_int* ldh
                          , nt2_la_complex* t,  const nt2_la_int* ldt
                          , nt2_la_complex* alpha, nt2_la_complex* beta
                          , nt2_la_complex* q,  const nt2_la_int* ldq
                          , nt2_la_complex* z,  const nt2_la_int* ldz
                          , nt2_la_complex* w,  nt2_la_int* lw, double* rw
                          , nt2_la_int* info
                          );


}

#endif
