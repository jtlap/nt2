##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

set( SOURCES
  inc.cpp
  dec.cpp
  ceil.cpp
  floor.cpp
  round.cpp
  round2even.cpp
  trunc.cpp
  oneminus.cpp
  oneplus.cpp
  minusone.cpp
  sqr_abs.cpp
  abs.cpp
  arg.cpp
  dist.cpp
  hypot.cpp
  sqrt.cpp
  fma.cpp
  average.cpp
  min.cpp
  max.cpp
  proj.cpp
  rec.cpp
  conj.cpp
   )

nt2_module_add_tests(type.complex.base.arithmetic.scalar.unit ${SOURCES})
