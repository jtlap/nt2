##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  negate.cpp
  sign.cpp
  negation.cpp
  sbits.cpp
  signnz.cpp
  prev.cpp
  next.cpp
  ulpdist.cpp
  ulp.cpp
  toint.cpp
  tofloat.cpp
  successor.cpp
  round2even.cpp
  predecessor.cpp
  nextpow2.cpp
  nextafter.cpp
  modf.cpp
  minnummag.cpp
  minnum.cpp
  minmag.cpp
  maxnummag.cpp
  maxnum.cpp
  maxmag.cpp
  mantissa.cpp
  ldexp.cpp
  ilogb.cpp
  frexp.cpp
  frac.cpp
  fast_ldexp.cpp
  fast_frexp.cpp
  exponentbits.cpp
  exponent.cpp
  eps.cpp
  copysign.cpp
  bitofsign.cpp
  bitinteger.cpp
  bitfloating.cpp
# List of simd test files for toolbox ieee
   )

##############################################################################
# For each filename
##############################################################################
FOREACH( EXAMPLE ${SOURCES})
  ############################################################################
  ## Build the executable filename from the example source filename
  ############################################################################
  STRING(REGEX REPLACE ".cpp" ".ieee.simd.bench" EXECUTABLE "${EXAMPLE}")
  STRING(REGEX REPLACE ".cpp" "-ieee.simd.bench" TEST "${EXAMPLE}")

  ############################################################################
  ## Add as a target
  ############################################################################
  ADD_EXECUTABLE(${EXECUTABLE} ${EXAMPLE})
  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)
  SET_TARGET_PROPERTIES(${EXECUTABLE} PROPERTIES COMPILE_FLAGS ${NT2_CXX_SIMD_FLAGS})
  ADD_TEST(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})
ENDFOREACH()