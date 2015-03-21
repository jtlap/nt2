//==============================================================================
//         Copyright 2015 - Jean-Thierry Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_DECLARE_GGHRD_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_DECLARE_GGHRD_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

/// Lapack declaration interface
///
/// excerpt from LAPACK documentation
// /// FOR ? C or Z
// *  ?GGHRD reduces a pair of complex matrices (A,B) to generalized upper
// *  Hessenberg form using unitary transformations, where A is a
// *  general matrix and B is upper triangular.  The form of the generalized
// *  eigenvalue problem is
// *     A*x = lambda*B*x,
// *  and B is typically made upper triangular by computing its QR
// *  factorization and moving the unitary matrix Q to the left side
// *  of the equation.
// *
// *  This subroutine simultaneously reduces A to a Hessenberg matrix H:
// *     Q**H*A*Z = H
// *  and transforms B to another upper triangular matrix T:
// *     Q**H*B*Z = T
// *  in order to reduce the problem to its standard form
// *     H*y = lambda*T*y
// *  where y = Z**H*x.
// *
// *  The unitary matrices Q and Z are determined as products of Givens
// *  rotations.  They may either be formed explicitly, or they may be
// *  postmultiplied into input matrices Q1 and Z1, so that
// *       Q1 * A * Z1**H = (Q1*Q) * H * (Z1*Z)**H
// *       Q1 * B * Z1**H = (Q1*Q) * T * (Z1*Z)**H
// *  If Q1 is the unitary matrix from the QR factorization of B in the
// *  original equation A*x = lambda*B*x, then CGGHRD reduces the original
// *  problem to generalized Hessenberg form.
// *
// *  Arguments
// *  =========
// *
// *  COMPQ   (input) CHARACTER*1
// *          = 'N': do not compute Q;
// *          = 'I': Q is initialized to the unit matrix, and the
// *                 unitary matrix Q is returned;
// *          = 'V': Q must contain a unitary matrix Q1 on entry,
// *                 and the product Q1*Q is returned.
// *
// *  COMPZ   (input) CHARACTER*1
// *          = 'N': do not compute Q;
// *          = 'I': Q is initialized to the unit matrix, and the
// *                 unitary matrix Q is returned;
// *          = 'V': Q must contain a unitary matrix Q1 on entry,
// *                 and the product Q1*Q is returned.
// *
// *  N       (input) INTEGER
// *          The order of the matrices A and B.  N >= 0.
// *
// *  ILO     (input) INTEGER
// *  IHI     (input) INTEGER
// *          ILO and IHI mark the rows and columns of A which are to be
// *          reduced.  It is assumed that A is already upper triangular
// *          in rows and columns 1:ILO-1 and IHI+1:N.  ILO and IHI are
// *          normally set by a previous call to CGGBAL; otherwise they
// *          should be set to 1 and N respectively.
// *          1 <= ILO <= IHI <= N, if N > 0; ILO=1 and IHI=0, if N=0.
// *
// *  A       (input/output)  array, dimension (LDA, N)
// *          On entry, the N-by-N general matrix to be reduced.
// *          On exit, the upper triangle and the first subdiagonal of A
// *          are overwritten with the upper Hessenberg matrix H, and the
// *          rest is set to zero.
// *
// *  LDA     (input) INTEGER
// *          The leading dimension of the array A.  LDA >= max(1,N).
// *
// *  B       (input/output)  array, dimension (LDB, N)
// *          On entry, the N-by-N upper triangular matrix B.
// *          On exit, the upper triangular matrix T = Q**H B Z.  The
// *          elements below the diagonal are set to zero.
// *
// *  LDB     (input) INTEGER
// *          The leading dimension of the array B.  LDB >= max(1,N).
// *
// *  Q       (input/output)  array, dimension (LDQ, N)
// *          On entry, if COMPQ = 'V', the unitary matrix Q1, typically
// *          from the QR factorization of B.
// *          On exit, if COMPQ='I', the unitary matrix Q, and if
// *          COMPQ = 'V', the product Q1*Q.
// *          Not referenced if COMPQ='N'.
// *
// *  LDQ     (input) INTEGER
// *          The leading dimension of the array Q.
// *          LDQ >= N if COMPQ='V' or 'I'; LDQ >= 1 otherwise.
// *
// *  Z       (input/output)  array, dimension (LDZ, N)
// *          On entry, if COMPZ = 'V', the unitary matrix Z1.
// *          On exit, if COMPZ='I', the unitary matrix Z, and if
// *          COMPZ = 'V', the product Z1*Z.
// *          Not referenced if COMPZ='N'.
// *
// *  LDZ     (input) INTEGER
// *          The leading dimension of the array Z.
// *          LDZ >= N if COMPZ='V' or 'I'; LDZ >= 1 otherwise.
// *
// *  INFO    (output) INTEGER
// *          = 0:  successful exit.
// *          < 0:  if INFO = -i, the i-th argument had an illegal value.
// *
extern "C"

{
  void NT2_F77NAME(dgghrd)( const char* compq,   const char* compz
                          , const nt2_la_int* n , const nt2_la_int* ilo, const nt2_la_int* ihi
                          , double* a,  const nt2_la_int* lda
                          , double* b,  const nt2_la_int* ldb
                          , double* q,  const nt2_la_int* ldq
                          , double* z,  const nt2_la_int* ldz
                          , nt2_la_int* info
                          );
  void NT2_F77NAME(sgghrd)( const char* compq,   const char* compz
                          , const nt2_la_int* n , const nt2_la_int* ilo, const nt2_la_int* ihi
                          , float* a,  const nt2_la_int* lda
                          , float* b,  const nt2_la_int* ldb
                          , float* q,  const nt2_la_int* ldq
                          , float* z,  const nt2_la_int* ldz
                          , nt2_la_int* info
                          );
  void NT2_F77NAME(cgghrd)( const char* compq,   const char* compz
                          ,  const nt2_la_int* n , const nt2_la_int* ilo, const nt2_la_int* ihi
                          , nt2_la_complex* a,  const nt2_la_int* lda
                          , nt2_la_complex* b,  const nt2_la_int* ldb
                          , nt2_la_complex* q,  const nt2_la_int* ldq
                          , nt2_la_complex* z,  const nt2_la_int* ldz
                          , nt2_la_int* info
                          );
  void NT2_F77NAME(zgghrd)( const char* compq,   const char* compz
                          , const nt2_la_int* n , const nt2_la_int* ilo, const nt2_la_int* ihi
                          , nt2_la_complex* a,  const nt2_la_int* lda
                          , nt2_la_complex* b,  const nt2_la_int* ldb
                          , nt2_la_complex* q,  const nt2_la_int* ldq
                          , nt2_la_complex* z,  const nt2_la_int* ldz
                          , nt2_la_int* info
                          );


}

#endif
