##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  sin.cpp
  acos.cpp
  log10.cpp
  cosh.cpp
  tan.cpp
  exp.cpp
  sinh.cpp
  abs.cpp
  atan2.cpp
  frexp.cpp
  ceil.cpp
  sqrt.cpp
  fmod.cpp
  tanh.cpp
  pow.cpp
  atan.cpp
  floor.cpp
  fabs.cpp
  log.cpp
  cos.cpp
  asin.cpp
# List of scalar test files for toolbox standard
   )

nt2_module_add_tests(extern.standard.scalar.unit ${SOURCES})
