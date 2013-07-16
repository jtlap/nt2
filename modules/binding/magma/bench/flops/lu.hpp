//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef FLOPS_LU_HPP_INCLUDED
#define FLOPS_LU_HPP_INCLUDED

/*
  FLOP for LU from LAPACK Working Note 41
*/

#define FLOPS_GETRF(m, n) ( FMULS_GETRF((double)(m), (double)(n))              \
                          + FADDS_GETRF((double)(m), (double)(n))              \
                          )                                                    \
/**/

#define FMULS_GETRF(m, n)   ( ((m) < (n))                                      \
                            ? ( 0.5 * (m) * ( (m) * ((n) - (1./3.) * (m) - 1. )\
                                            + (n)                              \
                                            )                                  \
                                + (2. / 3.) * (m)                              \
                              )                                                \
                            : ( 0.5 * (n) * ( (n) * ((m) - (1./3.) * (n) - 1. )\
                                            + (m)                              \
                                            )                                  \
                                + (2. / 3.) * (n))                             \
                            )                                                  \
/**/

#define FADDS_GETRF(m, n)   ( ((m) < (n))                                      \
                            ? (0.5 * (m)  * (  (m) * ((n) - (1./3.) * (m))     \
                                            - (n)) + (1. / 6.) * (m)           \
                                            )                                  \
                            : (0.5 * (n)  * ( (n) * ((m) - (1./3.) * (n))      \
                                            - (m)) + (1. / 6.) * (n)           \
                                            )                                  \
                            )                                                  \
/**/

#endif
