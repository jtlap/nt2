##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  sinhc.cpp
  tanh.cpp
  sinh.cpp
  sech.cpp
  csch.cpp
  coth.cpp
  cosh.cpp
  atanh.cpp
  asinh.cpp
  asech.cpp
  acsch.cpp
  acoth.cpp
  acosh.cpp
# List of simd test files for toolbox hyperbolic
   )

##############################################################################
# For each filename
##############################################################################
FOREACH( EXAMPLE ${SOURCES})
  ############################################################################
  ## Build the executable filename from the example source filename
  ############################################################################
  STRING(REGEX REPLACE ".cpp" ".hyperbolic.simd.unit" EXECUTABLE "${EXAMPLE}")
  STRING(REGEX REPLACE ".cpp" "-hyperbolic.simd.unit" TEST "${EXAMPLE}")

  ############################################################################
  ## Add as a target
  ############################################################################
  ADD_EXECUTABLE(${EXECUTABLE} ${EXAMPLE})
  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)
  SET_TARGET_PROPERTIES(${EXECUTABLE} PROPERTIES COMPILE_FLAGS ${NT2_CXX_SIMD_FLAGS})
  ADD_TEST(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})
ENDFOREACH()