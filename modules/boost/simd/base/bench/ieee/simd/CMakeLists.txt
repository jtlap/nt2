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
  exponent.cpp
  exponentbits.cpp
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
  next.cpp
  nextafter.cpp
  nextpow2.cpp
  predecessor.cpp
  prev.cpp
  sbits.cpp
  sign.cpp
  signnz.cpp
  successor.cpp
  ulp.cpp
  ulpdist.cpp
   )

nt2_module_add_tests(boost.simd.base.ieee.simd.bench ${SOURCES})
