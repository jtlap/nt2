##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

set( SOURCES
  asin.cpp
  acos.cpp
  atan.cpp
  cos.cpp
  sin.cpp
  tan.cpp
  cot.cpp
  cosd.cpp
  cospi.cpp
  sind.cpp
  tand.cpp
  sinpi.cpp
  tanpi.cpp
   )

nt2_module_add_tests(complex.trigonometric.scalar.unit ${SOURCES})
