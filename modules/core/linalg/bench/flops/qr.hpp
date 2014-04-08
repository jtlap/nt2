//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef FLOPS_QR_HPP_INCLUDED
#define FLOPS_QR_HPP_INCLUDED

/*
  FLOP for QR from LAPACK Working Note 41
*/
#define FLOPS_GEQRF(m, n)  ( FMULS_GEQRF((double)(m), (double)(n))             \
                            + FADDS_GEQRF((double)(m), (double)(n))            \
                            )                                                  \
/**/

#define FMULS_GEQRF(m, n) ( ((m) > (n))                                        \
                          ? ( (n) * ( (n) * (  0.5-(1./3.) * (n) + (m))        \
                                    + (m) + 23. / 6.                           \
                                    )                                          \
                            )                                                  \
                          : ( (m) * ( (m) * ( -0.5-(1./3.) * (m) + (n))        \
                                    + 2.*(n) + 23. / 6.                        \
                                    )                                          \
                            )                                                  \
                          )                                                    \
/**/

#define FADDS_GEQRF(m, n) ( ((m) > (n))                                        \
                          ? ((n)  * ( (n) * (  0.5-(1./3.) * (n) + (m))        \
                                          +  5. / 6.)                          \
                                    )                                          \
                          : ((m)  * ( (m) * ( -0.5-(1./3.) * (m) + (n))        \
                                    + (n) +  5. / 6.)                          \
                                    )                                          \
                          )                                                    \
/**/

#define FLOPS_ORGQR(m, n, k)                                                   \
( FMULS_UNGQR((double)(m),(double)(n),(double)(k))                             \
+ FADDS_UNGQR((double)(m),(double)(n),(double)(k))                             \
)                                                                              \
/**/

#define FMULS_UNGQR(m, n, k)  ( (k) * ( 2.* (m) * (n) +    2. * (n)            \
                                      - 5./3. + (k)                            \
                                      * (2./3. * (k) - ((m) + (n)) - 1.)       \
                                      )                                        \
                              )                                                \
/**/

#define FADDS_UNGQR(m, n, k)  ( (k) * ( 2.* (m) * (n) + (n)                    \
                                      - (m) + 1./3. + (k)                      \
                                      * (2./3. * (k) - ((m) + (n)))            \
                                      )                                        \
                              )                                                \
/**/

#define FLOPS_ORMQR(m, n, k)                                                   \
( FMULS_UNGQR((double)(m),(double)(n),(double)(k))                             \
+ FADDS_UNGQR((double)(m),(double)(n),(double)(k))                             \
)                                                                              \
/**/

#define FMULS_UNMQR(m, n, k)  (2.*(n)*(m)*(k) - (n)*(k)*(k) + 2.*(n)*(k))
#define FADDS_UNMQR(m, n, k)  (2.*(n)*(m)*(k) - (n)*(k)*(k) + (n)*(k))

#endif
