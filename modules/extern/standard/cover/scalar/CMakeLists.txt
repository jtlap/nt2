
################################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
  tanh.cpp
  tan.cpp
  sqrt.cpp
  sinh.cpp
  sin.cpp
  pow.cpp
  log10.cpp
  log.cpp
  frexp.cpp
  fmod.cpp
  floor.cpp
  fabs.cpp
  exp.cpp
  cosh.cpp
  cos.cpp
  ceil.cpp
  atan2.cpp
  atan.cpp
  asin.cpp
  acos.cpp
  abs.cpp
# List of scalar test files for toolbox standard
   )

nt2_module_add_tests(extern.standard.scalar.cover ${SOURCES})

