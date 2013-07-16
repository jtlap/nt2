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

#endif
