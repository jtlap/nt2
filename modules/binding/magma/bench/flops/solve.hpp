//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef FLOPS_SOLVE_HPP_INCLUDED
#define FLOPS_SOLVE_HPP_INCLUDED

/*
  FLOP for LU from LAPACK Working Note 41
*/
#define FLOPS_DGETRS(n, nrhs) ( FMULS_GETRS((double)(n), (double)(nrhs))       \
                              + FADDS_GETRS((double)(n), (double)(nrhs))       \
                              )                                                \
/**/

#define FMULS_GETRS(n, nrhs) ((nrhs) * (n) *  (n)      )
#define FADDS_GETRS(n, nrhs) ((nrhs) * (n) * ((n) - 1 ))


#define FMULS_POTRF(__n) ((__n) * (((1. / 6.) * (__n) + 0.5) * (__n) + (1. / 3.)))
#define FADDS_POTRF(__n) ((__n) * (((1. / 6.) * (__n)      ) * (__n) - (1. / 6.)))

#define FMULS_POTRS(__n, __nrhs) ((__nrhs) * (__n) * ((__n) + 1 ))
#define FADDS_POTRS(__n, __nrhs) ((__nrhs) * (__n) * ((__n) - 1 ))

#define FLOPS_DPOTRF(__n) (     FMULS_POTRF((double)(__n)) +       FADDS_POTRF((double)(__n)) )
#define FLOPS_SPOTRF(__n) (     FMULS_POTRF((double)(__n)) +       FADDS_POTRF((double)(__n)) )


#define FLOPS_DPOTRS(__n, __nrhs) (     FMULS_POTRS((double)(__n), (double)(__nrhs)) +       FADDS_POTRS((double)(__n), (double)(__nrhs)) )
#define FLOPS_SPOTRS(__n, __nrhs) (     FMULS_POTRS((double)(__n), (double)(__nrhs)) +       FADDS_POTRS((double)(__n), (double)(__nrhs)) )
#endif
