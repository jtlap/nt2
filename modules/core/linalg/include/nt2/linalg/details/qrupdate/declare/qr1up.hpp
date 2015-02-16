//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_QRUPDATE_DECLARE_QR1UP_HPP_INCLUDED
#define NT2_LINALG_DETAILS_QRUPDATE_DECLARE_QR1UP_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>


/* excerpt from qr1up.f
**
** purpose:      updates a qr factorization after rank-1 modification
**               i.e., given a m-by-k orthogonal q and m-by-n upper
**               trapezoidal r, an m-vector u and n-vector v,
**               this subroutine updates q -> q1 and r -> r1 so that
**               q1*r1 = q*r + u*v', and q1 is again orthonormal
**               and r1 upper trapezoidal.
**               (real version)
**
** m (in)        number of rows of the matrix q.
** n (in)        number of columns of the matrix r.
** k (in)        number of columns of q, and rows of r. must be
**               either k = m (full q) or k = n < m (economical form).
** q (io)        on entry, the orthogonal m-by-k matrix q.
**               on exit, the updated matrix q1.
** ldq (in)      the leading dimension of q. ldq >= m.
** r (io)        on entry, the upper trapezoidal m-by-n matrix r..
**               on exit, the updated matrix r1.
** ldr (in)      the leading dimension of r. ldr >= k.
** u (io)        the left m-vector. on exit, if k < m, u is destroyed.
** v (io)        the right n-vector. on exit, v is destroyed.
** w (out)       a workspace vector of size 2*k
**
**/

extern "C"
{
  void NT2_F77NAME(cqr1up)(const nt2_la_int* m  , const nt2_la_int* n
                          , const nt2_la_int* k
                          , nt2_la_complex* q   , const nt2_la_int* ldq
                          , nt2_la_complex* r   , const nt2_la_int* ldr
                          , nt2_la_complex* u   , nt2_la_complex* v
                          , nt2_la_complex* w   , float* rw);
  void NT2_F77NAME(zqr1up)(const nt2_la_int* m  , const nt2_la_int* n
                          , const nt2_la_int* k
                          , nt2_la_complex* q   , const nt2_la_int* ldq
                          , nt2_la_complex* r   , const nt2_la_int* ldr
                          , nt2_la_complex* u   , nt2_la_complex* v
                          , nt2_la_complex* w   , double* rw);
  void NT2_F77NAME(sqr1up)(const nt2_la_int* m  , const nt2_la_int* n
                          , const nt2_la_int* k
                          , float* q , const nt2_la_int* ldq
                          , float* r , const nt2_la_int* ldr
                          , float* u , nt2_la_complex* v
                          , float* w);
  void NT2_F77NAME(dqr1up)(const nt2_la_int* m   , const nt2_la_int* n
                          , const nt2_la_int* k
                          , double* q , const nt2_la_int* ldq
                          , double* r , const nt2_la_int* ldr
                          , double* u , double* v
                          , double* w);
}

#endif
