##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  sqr_abs.cpp
  isqrt.cpp
  negs.cpp
  fast_toint.cpp
  abss.cpp
  adds.cpp
  subs.cpp
  divs.cpp
  muls.cpp
  divround.cpp
  divfloor.cpp
  divfix.cpp
  divceil.cpp
  random.cpp
  logical_xor.cpp
  ifloor.cpp
  fast_hypot.cpp
  iround.cpp
  arg.cpp
  iround2even.cpp
  remainder.cpp
  rem.cpp
  mod.cpp
  remquo.cpp
  minmod.cpp
  iceil.cpp
  trunc.cpp
  ceil.cpp
  round.cpp
  floor.cpp
  two_split.cpp
  two_prod.cpp
  two_add.cpp
  rsqrt.cpp
  sqrt.cpp
  sqr.cpp
  rec.cpp
  oneplus.cpp
  oneminus.cpp
  minusone.cpp
  min.cpp
  max.cpp
  idivround.cpp
  idivfloor.cpp
  idivfix.cpp
  idivceil.cpp
  hypot.cpp
  fma.cpp
  dist.cpp
  correct_fma.cpp
  average.cpp
  abs.cpp
  toint.cpp
  tofloat.cpp
# List of scalar test files for toolbox arithmetic
   )

nt2_module_add_tests(boost.simd.arithmetic.scalar.unit ${SOURCES})
