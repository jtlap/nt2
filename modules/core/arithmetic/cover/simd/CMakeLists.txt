
################################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
  isqrt.cpp
  two_split.cpp
  two_prod.cpp
  two_add.cpp
  trunc.cpp
  toint.cpp
  tofloat.cpp
  subs.cpp
  sqrt.cpp
  sqr.cpp
  rsqrt.cpp
  round.cpp
  remquo.cpp
  remainder.cpp
  rem.cpp
  rec.cpp
  random.cpp
  oneplus.cpp
  oneminus.cpp
  negs.cpp
  muls.cpp
  mod.cpp
  minusone.cpp
  minmod.cpp
  min.cpp
  max.cpp
  logical_xor.cpp
  iround.cpp
  ifloor.cpp
  idivround.cpp
  idivfloor.cpp
  idivfix.cpp
  idivceil.cpp
  iceil.cpp
  hypot.cpp
  fma.cpp
  fast_toint.cpp
  fast_hypot.cpp
  divs.cpp
  divround.cpp
  divfloor.cpp
  divfix.cpp
  divceil.cpp
  dist.cpp
  correct_fma.cpp
  ceil.cpp
  average.cpp
  arg.cpp
  adds.cpp
  abss.cpp
  abs.cpp
  floor.cpp
# List of simd test files for toolbox arithmetic
   )

nt2_module_add_tests(core.arithmetic.simd.cover ${SOURCES})

