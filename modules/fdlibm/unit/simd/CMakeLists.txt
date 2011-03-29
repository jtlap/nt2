##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  gamma.cpp
  log1p.cpp
  modf.cpp
  exp.cpp
  __ieee754_jn.cpp
  erfc.cpp
  erf.cpp
  atan2.cpp
  tanh.cpp
  expm1.cpp
  ldexp.cpp
  __ieee754_sinh.cpp
  acos.cpp
  remainder.cpp
  significand.cpp
  sinh.cpp
  __ieee754_pow.cpp
  jn.cpp
  ceil.cpp
  __ieee754_asin.cpp
  __ieee754_log10.cpp
  __ieee754_gamma.cpp
  __ieee754_hypot.cpp
  __ieee754_yn.cpp
  yn.cpp
  atan.cpp
  fmod.cpp
  scalbn.cpp
  asinh.cpp
  __ieee754_sqrt.cpp
  nextafter.cpp
  sin.cpp
  log10.cpp
  finite.cpp
  __ieee754_cosh.cpp
  pow.cpp
  __ieee754_fmod.cpp
  cbrt.cpp
  __ieee754_lgamma.cpp
  __ieee754_atan2.cpp
  frexp.cpp
  lgamma.cpp
  sqrt.cpp
  __ieee754_acosh.cpp
  ilogb.cpp
  __ieee754_j0.cpp
  __ieee754_j1.cpp
  cos.cpp
  __ieee754_y1.cpp
  floor.cpp
  fabs.cpp
  log.cpp
  isnan.cpp
  asin.cpp
  tan.cpp
  __ieee754_acos.cpp
  y1.cpp
  __ieee754_exp.cpp
  __ieee754_y0.cpp
  logb.cpp
  hypot.cpp
  __ieee754_atanh.cpp
  __ieee754_log.cpp
  cosh.cpp
  j1.cpp
  j0.cpp
  acosh.cpp
  rint.cpp
  y0.cpp
  atanh.cpp
  __ieee754_remainder.cpp
# List of simd test files for toolbox fdlibm
   )

##****************************************************************************
# For each filename
##****************************************************************************
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_unit(fdlibm.simd.${EXAMPLE}.unit ${EXAMPLE}.cpp)
ENDFOREACH()
