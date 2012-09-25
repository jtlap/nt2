
################################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
  yn.cpp
  y1.cpp
  y0.cpp
  tanh.cpp
  tan.cpp
  sqrt.cpp
  sinh.cpp
  sin.cpp
  significand.cpp
  scalbn.cpp
  rint.cpp
  remainder.cpp
  pow.cpp
  nextafter.cpp
  modf.cpp
  logb.cpp
  log1p.cpp
  log10.cpp
  log.cpp
  lgamma.cpp
  ldexp.cpp
  jn.cpp
  j1.cpp
  j0.cpp
  isnan.cpp
  ilogb.cpp
  hypot.cpp
  gamma.cpp
  frexp.cpp
  fmod.cpp
  floor.cpp
  finite.cpp
  fabs.cpp
  expm1.cpp
  exp.cpp
  erfc.cpp
  erf.cpp
  cosh.cpp
  cos.cpp
  ceil.cpp
  cbrt.cpp
  atanh.cpp
  atan2.cpp
  atan.cpp
  asinh.cpp
  asin.cpp
  acosh.cpp
  acos.cpp
  __ieee754_yn.cpp
  __ieee754_y1.cpp
  __ieee754_y0.cpp
  __ieee754_sqrt.cpp
  __ieee754_sinh.cpp
  __ieee754_remainder.cpp
  __ieee754_pow.cpp
  __ieee754_log10.cpp
  __ieee754_log.cpp
  __ieee754_lgamma.cpp
  __ieee754_jn.cpp
  __ieee754_j1.cpp
  __ieee754_j0.cpp
  __ieee754_hypot.cpp
  __ieee754_gamma.cpp
  __ieee754_fmod.cpp
  __ieee754_exp.cpp
  __ieee754_cosh.cpp
  __ieee754_atanh.cpp
  __ieee754_atan2.cpp
  __ieee754_asin.cpp
  __ieee754_acosh.cpp
  __ieee754_acos.cpp
# List of scalar test files for toolbox fdlibm
   )

nt2_module_add_tests(extern.fdlibm.scalar.cover ${SOURCES})

