##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  atanpi.cpp
  asinpi.cpp
  acospi.cpp
  tanpi.cpp
  tand.cpp
  tan.cpp
  sinpi.cpp
  sind.cpp
  sincospi.cpp
  sincosd.cpp
  sincos.cpp
  sin.cpp
  secpi.cpp
  secd.cpp
  sec.cpp
  inrad.cpp
  indeg.cpp
  fast_tanpi.cpp
  fast_tand.cpp
  fast_tan.cpp
  fast_sinpi.cpp
  fast_sind.cpp
  fast_sincospi.cpp
  fast_sincosd.cpp
  fast_sincos.cpp
  fast_sin.cpp
  fast_cotpi.cpp
  fast_cotd.cpp
  fast_cot.cpp
  fast_cospi.cpp
  fast_cosd.cpp
  fast_cos.cpp
  cscpi.cpp
  cscd.cpp
  csc.cpp
  cotpi.cpp
  cotd.cpp
  cot.cpp
  cospi.cpp
  cosd.cpp
  cos.cpp
  atand.cpp
  atan2.cpp
  atan.cpp
  asind.cpp
  asin.cpp
  asecd.cpp
  asec.cpp
  acscd.cpp
  acsc.cpp
  acotd.cpp
  acot.cpp
  acosd.cpp
  acos.cpp
# List of scalar test files for toolbox trigonometric
   )

##############################################################################
# For each filename
##############################################################################
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_bench(trigonometric.scalar.${EXAMPLE}.bench ${EXAMPLE}.cpp)
ENDFOREACH()
