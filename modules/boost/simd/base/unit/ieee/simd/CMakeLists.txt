##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  bitfloating.cpp
  bitinteger.cpp
  bitofsign.cpp
  copysign.cpp
  eps.cpp
  exponentbits.cpp
  exponent.cpp
  fast_frexp.cpp
  fast_ldexp.cpp
  frac.cpp
  frexp.cpp
  ilogb.cpp
  ldexp.cpp
  mantissa.cpp
  maxmag.cpp
  maxnum.cpp
  maxnummag.cpp
  minmag.cpp
  minnum.cpp
  minnummag.cpp
  modf.cpp
  negate.cpp
  nextafter.cpp
  next.cpp
  nextpow2.cpp
  predecessor.cpp
  prev.cpp
  saturate_at.cpp
  saturate.cpp
  sbits.cpp
  sign.cpp
  signnz.cpp
  successor.cpp
  ulp.cpp
  ulpdist.cpp
# List of simd test files for toolbox ieee
   )

nt2_module_add_tests(boost.simd.base.ieee.simd.unit ${SOURCES})
