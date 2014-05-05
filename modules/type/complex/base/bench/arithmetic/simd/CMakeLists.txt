##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  # List of simd test files for toolbox arithmetic
  abs.cpp
  arg.cpp
  average.cpp
  ceil.cpp
  conj.cpp
  dec.cpp
  dist.cpp
  floor.cpp
  fma.cpp
  fms.cpp
  fnma.cpp
  fnms.cpp
  hypot.cpp
  inc.cpp
  max.cpp
  min.cpp
  minusone.cpp
  oneminus.cpp
  rec.cpp
  round2even.cpp
  round.cpp
  rsqrt.cpp
  sqr.cpp
  sqr_abs.cpp
  sqrt.cpp
  trunc.cpp
  )

nt2_module_add_tests(type.complex.base.arithmetic.simd.bench ${SOURCES})
