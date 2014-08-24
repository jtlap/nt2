#ifndef NT2_LINALG_DETAILS_LAPACK_DECLARE_HSTRF_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_DECLARE_HSTRF_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
// contrarily to lapack we use sym matrix in real case ans hermitian in complex case
// this means that hstrf calls respectively xsytrf ans xhetrf
//     **  purpose
//     **  =======
//     **
//     **  xsytrf computes the factorization of a DATA TYPE symmetric matrix a
//     **  using the bunch-kaufman diagonal pivoting method.  the form of the
//     **  factorization is
//     **
//     **     a = u*d*u**t  or  a = l*d*l**t
//     **
//     **  where u (or l) is a product of permutation and unit upper (lower)
//     **  triangular matrices, and d is symmetric and block diagonal with
//     **  with 1-by-1 and 2-by-2 diagonal blocks.
//     **
//     **  this is the blocked version of the algorithm, calling level 3 blas.
//     **
//     **  arguments
//     **  =========
//     **
//     **  uplo    (input) char
//     **          = 'u':  upper triangle of a is stored;
//     **          = 'l':  lower triangle of a is stored.
//     **
//     **  n       (input) long int
//     **          the order of the matrix a.  n >= 0.
//     **
//     **  a       (input/output) DATA TYPE array, dimension (lda,n)
//     **          on entry, the symmetric matrix a.  if uplo = 'u', the leading
//     **          n-by-n upper triangular part of a contains the upper
//     **          triangular part of the matrix a, and the strictly lower
//     **          triangular part of a is not referenced.  if uplo = 'l', the
//     **          leading n-by-n lower triangular part of a contains the lower
//     **          triangular part of the matrix a, and the strictly upper
//     **          triangular part of a is not referenced.
//     **
//     **          on exit, the block diagonal matrix d and the multipliers used
//     **          to obtain the factor u or l (see below for further details).
//     **
//     **  lda     (input) long int
//     **          the leading dimension of the array a.  lda >= max(1,n).
//     **
//     **  ipiv    (output) long int array, dimension (n)
//     **          details of the interchanges and the block structure of d.
//     **          if ipiv(k) > 0, then rows and columns k and ipiv(k) were
//     **          interchanged and d(k,k) is a 1-by-1 diagonal block.
//     **          if uplo = 'u' and ipiv(k) = ipiv(k-1) < 0, then rows and
//     **          columns k-1 and -ipiv(k) were interchanged and d(k-1:k,k-1:k)
//     **          is a 2-by-2 diagonal block.  if uplo = 'l' and ipiv(k) =
//     **          ipiv(k+1) < 0, then rows and columns k+1 and -ipiv(k) were
//     **          interchanged and d(k:k+1,k:k+1) is a 2-by-2 diagonal block.
//     **
//     **  WORK    (workspace/output) REAL/COMPLEX array, dimension (MAX(1,LWORK))
//     **          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
//     **
//     **  LWORK   (input) INTEGER
//     **          The length of WORK.  LWORK >=1.  For best performance
//     **          LWORK >= N*NB, where NB is the block size returned by ILAENV.
//     **
//     **          If LWORK = -1, then a workspace query is assumed; the routine
//     **          only calculates the optimal size of the WORK array, returns
//     **          this value as the first entry of the WORK array, and no error
//     **          message related to LWORK is issued by XERBLA.//     **
//     **
//     **  info    (output) long int
//     **          = 0:  successful exit
//     **          < 0:  if info = -i, the i-th argument had an illegal value
//     **          > 0:  if info = i, d(i,i) is exactly zero.  the factorization
//     **                has been completed, but the block diagonal matrix d is
//     **                exactly singular, and division by zero will occur if it
//     **                is used to solve a system of equations.
//     **
//     **  further details
//     **  ===============
//     **
//     **  if uplo = 'u', then a = u*d*u', where
//     **     u = p(n)*u(n)* ... *p(k)u(k)* ...,
//     **  i.e., u is a product of terms p(k)*u(k), where k decreases from n to
//     **  1 in steps of 1 or 2, and d is a block diagonal matrix with 1-by-1
//     **  and 2-by-2 diagonal blocks d(k).  p(k) is a permutation matrix as
//     **  defined by ipiv(k), and u(k) is a unit upper triangular matrix, such
//     **  that if the diagonal block d(k) is of order s (s = 1 or 2), then
//     **
//     **             (   i    v    0   )   k-s
//     **     u(k) =  (   0    i    0   )   s
//     **             (   0    0    i   )   n-k
//     **                k-s   s   n-k
//     **
//     **  if s = 1, d(k) overwrites a(k,k), and v overwrites a(1:k-1,k).
//     **  if s = 2, the upper triangle of d(k) overwrites a(k-1,k-1), a(k-1,k),
//     **  and a(k,k), and v overwrites a(1:k-2,k-1:k).
//     **
//     **  if uplo = 'l', then a = l*d*l', where
//     **     l = p(1)*l(1)* ... *p(k)*l(k)* ...,
//     **  i.e., l is a product of terms p(k)*l(k), where k increases from 1 to
//     **  n in steps of 1 or 2, and d is a block diagonal matrix with 1-by-1
//     **  and 2-by-2 diagonal blocks d(k).  p(k) is a permutation matrix as
//     **  defined by ipiv(k), and l(k) is a unit lower triangular matrix, such
//     **  that if the diagonal block d(k) is of order s (s = 1 or 2), then
//     **
//     **             (   i    0     0   )  k-1
//     **     l(k) =  (   0    i     0   )  s
//     **             (   0    v     i   )  n-k-s+1
//     **                k-1   s  n-k-s+1
//     **
//     **  if s = 1, d(k) overwrites a(k,k), and v overwrites a(k+1:n,k).
//     **  if s = 2, the lower triangle of d(k) overwrites a(k,k), a(k+1,k),
//     **  and a(k+1,k+1), and v overwrites a(k+2:n,k:k+1).
//     **

extern "C"

{
  void NT2_F77NAME(chetrf)(const char* uplo, const nt2_la_int* n
                          , nt2_la_complex* a, const nt2_la_int* lda
                          , nt2_la_int* ipiv
                          , nt2_la_complex* work, const nt2_la_int* lwork
                          , nt2_la_int* info);
  void NT2_F77NAME(zhetrf)(const char* uplo, const nt2_la_int* n
                          , nt2_la_complex* a, const nt2_la_int* lda
                          , nt2_la_int* ipiv
                          , nt2_la_complex* work, const nt2_la_int* lwork
                          , nt2_la_int* info);
  void NT2_F77NAME(ssytrf)(const char* uplo, const nt2_la_int* n
                          , float* a, const nt2_la_int* lda
                          , nt2_la_int* ipiv
                          , float* work, const nt2_la_int* lwork
                          , nt2_la_int* info);
  void NT2_F77NAME(dsytrf)(const char* uplo, const nt2_la_int* n
                          , double* a,
                       const nt2_la_int* lda
                          , nt2_la_int* ipiv
                          , double* work, const nt2_la_int* lwork
                          , nt2_la_int* info);
}

#endif
