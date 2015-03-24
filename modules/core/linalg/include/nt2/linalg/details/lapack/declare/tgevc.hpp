//==============================================================================
//         Copyright 2015 - Jean-Thierry Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_DECLARE_TGEVC_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_DECLARE_TGEVC_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

/// Lapack declaration interface
///
/// excerpt from LAPACK documentation
// /// FOR ? s, d, C or Z
//  ?TGEVC computes some or all of the right and/or left eigenvectors of
// *  a pair of real matrices (S,P), where S is a quasi-triangular matrix
// *  and P is upper triangular.  Matrix pairs of this type are produced by
// *  the generalized Schur factorization of a matrix pair (A,B):
// *
// *     A = Q*S*Z**T,  B = Q*P*Z**T
// *
// *  as computed by SGGHRD + SHGEQZ.
// *
// *  The right eigenvector x and the left eigenvector y of (S,P)
// *  corresponding to an eigenvalue w are defined by:
// *
// *     S*x = w*P*x,  (y**H)*S = w*(y**H)*P,
// *
// *  where y**H denotes the conjugate tranpose of y.
// *  The eigenvalues are not input to this routine, but are computed
// *  directly from the diagonal blocks of S and P.
// *
// *  This routine returns the matrices X and/or Y of right and left
// *  eigenvectors of (S,P), or the products Z*X and/or Q*Y,
// *  where Z and Q are input matrices.
// *  If Q and Z are the orthogonal factors from the generalized Schur
// *  factorization of a matrix pair (A,B), then Z*X and Q*Y
// *  are the matrices of right and left eigenvectors of (A,B).
// *
// *  Arguments
// *  =========
// *
// *  SIDE    (input) CHARACTER*1
// *          = 'R': compute right eigenvectors only;
// *          = 'L': compute left eigenvectors only;
// *          = 'B': compute both right and left eigenvectors.
// *
// *  HOWMNY  (input) CHARACTER*1
// *          = 'A': compute all right and/or left eigenvectors;
// *          = 'B': compute all right and/or left eigenvectors,
// *                 backtransformed by the matrices in VR and/or VL;
// *          = 'S': compute selected right and/or left eigenvectors,
// *                 specified by the logical array SELECT.
// *
// *  SELECT  (input) LOGICAL array, dimension (N)
// *          If HOWMNY='S', SELECT specifies the eigenvectors to be
// *          computed.  If w(j) is a real eigenvalue, the corresponding
// *          real eigenvector is computed if SELECT(j) is .TRUE..
// *          If w(j) and w(j+1) are the real and imaginary parts of a
// *          complex eigenvalue, the corresponding complex eigenvector
// *          is computed if either SELECT(j) or SELECT(j+1) is .TRUE.,
// *          and on exit SELECT(j) is set to .TRUE. and SELECT(j+1) is
// *          set to .FALSE..
// *          Not referenced if HOWMNY = 'A' or 'B'.
// *
// *  N       (input) INTEGER
// *          The order of the matrices S and P.  N >= 0.
// *
// *  S       (input)  array, dimension (LDS,N)
// *          The upper quasi-triangular matrix S from a generalized Schur
// *          factorization, as computed by SHGEQZ.
// *
// *  LDS     (input) INTEGER
// *          The leading dimension of array S.  LDS >= max(1,N).
// *
// *  P       (input)  array, dimension (LDP,N)
// *          The upper triangular matrix P from a generalized Schur
// *          factorization, as computed by SHGEQZ.
// *          2-by-2 diagonal blocks of P corresponding to 2-by-2 blocks
// *          of S must be in positive diagonal form.
// *
// *  LDP     (input) INTEGER
// *          The leading dimension of array P.  LDP >= max(1,N).
// *
// *  VL      (input/output)  array, dimension (LDVL,MM)
// *          On entry, if SIDE = 'L' or 'B' and HOWMNY = 'B', VL must
// *          contain an N-by-N matrix Q (usually the orthogonal matrix Q
// *          of left Schur vectors returned by SHGEQZ).
// *          On exit, if SIDE = 'L' or 'B', VL contains:
// *          if HOWMNY = 'A', the matrix Y of left eigenvectors of (S,P);
// *          if HOWMNY = 'B', the matrix Q*Y;
// *          if HOWMNY = 'S', the left eigenvectors of (S,P) specified by
// *                      SELECT, stored consecutively in the columns of
// *                      VL, in the same order as their eigenvalues.
// *
// *          A complex eigenvector corresponding to a complex eigenvalue
// *          is stored in two consecutive columns, the first holding the
// *          real part, and the second the imaginary part.
// *
// *          Not referenced if SIDE = 'R'.
// *
// *  LDVL    (input) INTEGER
// *          The leading dimension of array VL.  LDVL >= 1, and if
// *          SIDE = 'L' or 'B', LDVL >= N.
// *
// *  VR      (input/output)  array, dimension (LDVR,MM)
// *          On entry, if SIDE = 'R' or 'B' and HOWMNY = 'B', VR must
// *          contain an N-by-N matrix Z (usually the orthogonal matrix Z
// *          of right Schur vectors returned by SHGEQZ).
// *
// *          On exit, if SIDE = 'R' or 'B', VR contains:
// *          if HOWMNY = 'A', the matrix X of right eigenvectors of (S,P);
// *          if HOWMNY = 'B' or 'b', the matrix Z*X;
// *          if HOWMNY = 'S' or 's', the right eigenvectors of (S,P)
// *                      specified by SELECT, stored consecutively in the
// *                      columns of VR, in the same order as their
// *                      eigenvalues.
// *
// *          A complex eigenvector corresponding to a complex eigenvalue
// *          is stored in two consecutive columns, the first holding the
// *          real part and the second the imaginary part.
// *
// *          Not referenced if SIDE = 'L'.
// *
// *  LDVR    (input) INTEGER
// *          The leading dimension of the array VR.  LDVR >= 1, and if
// *          SIDE = 'R' or 'B', LDVR >= N.
// *
// *  MM      (input) INTEGER
// *          The number of columns in the arrays VL and/or VR. MM >= M.
// *
// *  M       (output) INTEGER
// *          The number of columns in the arrays VL and/or VR actually
// *          used to store the eigenvectors.  If HOWMNY = 'A' or 'B', M
// *          is set to N.  Each selected real eigenvector occupies one
// *          column and each selected complex eigenvector occupies two
// *          columns.
// *
// *  WORK    (workspace)  array, dimension (6*N)
// *
// *  INFO    (output) INTEGER
// *          = 0:  successful exit.
// *          < 0:  if INFO = -i, the i-th argument had an illegal value.
// *          > 0:  the 2-by-2 block (INFO:INFO+1) does not have a complex
// *                eigenvalue.
// *
extern "C"

{
  void NT2_F77NAME(dtgevc)( const char* side,  const char* howmny,   const bool* select
                          , const nt2_la_int* n
                          , double* s,  const nt2_la_int* lds
                          , double* p,  const nt2_la_int* ldp
                          , double* vl,  const nt2_la_int* ldvl
                          , double* vr,  const nt2_la_int* ldvr
                          , nt2_la_int* m , nt2_la_int* mm
                          , double* w
                          , nt2_la_int* info
                          );
  void NT2_F77NAME(stgevc)( const char* side, const char* howmny,   const bool* select
                          , const nt2_la_int* n
                          , float* s,  const nt2_la_int* lds
                          , float* p,  const nt2_la_int* ldp
                          , float* vl,  const nt2_la_int* ldvl
                          , float* vr,  const nt2_la_int* ldvr
                          , nt2_la_int* m , nt2_la_int* mm
                          , float* w
                          , nt2_la_int* info
                          );
  void NT2_F77NAME(ctgevc)( const char* side, const char* howmny,   const bool* select
                          ,  const nt2_la_int* n
                          , nt2_la_complex* s,  const nt2_la_int* lds
                          , nt2_la_complex* p,  const nt2_la_int* ldp
                          , nt2_la_complex* vl,  const nt2_la_int* ldvl
                          , nt2_la_complex* vr,  const nt2_la_int* ldvr
                          , nt2_la_int* m , nt2_la_int* mm
                          , nt2_la_complex* w, float* rw
                          , nt2_la_int* info
                          );
  void NT2_F77NAME(ztgevc)( const char* side, const char* howmny,   const bool* select
                          , const nt2_la_int* n
                          , nt2_la_complex* s,  const nt2_la_int* lds
                          , nt2_la_complex* p,  const nt2_la_int* ldp
                          , nt2_la_complex* vl,  const nt2_la_int* ldvl
                          , nt2_la_complex* vr,  const nt2_la_int* ldvr
                          , nt2_la_int* m , nt2_la_int* mm
                          , nt2_la_complex* w, double* rw
                          , nt2_la_int* info
                          );


}

#endif
