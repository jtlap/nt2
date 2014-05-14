##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
# List of scalar test files for toolbox trigonometric
  acos.cpp
#  acot.cpp
#  acsc.cpp
#  asec.cpp
  asin.cpp
  atan.cpp
  cos.cpp
  cospi.cpp
  cot.cpp
  csc.cpp
  cscpi.cpp
  sec.cpp
  secpi.cpp
#  sinc.cpp
  sincos.cpp
#  sincospi.cpp
  sin.cpp
  sinpi.cpp
  tan.cpp
  tanpi.cpp
)

nt2_module_add_tests(type.complex.trigonometric.simd.bench ${SOURCES})
