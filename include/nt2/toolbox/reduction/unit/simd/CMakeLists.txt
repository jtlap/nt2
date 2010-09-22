##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  sum.cpp
  second.cpp
  prod.cpp
  posmin.cpp
  posmax.cpp
  nbtrue.cpp
  minimum.cpp
  maximum.cpp
  first.cpp
  dot.cpp
  at.cpp
  all.cpp
  any.cpp
# List of simd test files for toolbox reduction
   )

##############################################################################
# For each filename
##############################################################################
FOREACH( EXAMPLE ${SOURCES})
  ############################################################################
  ## Build the executable filename from the example source filename
  ############################################################################
  STRING(REGEX REPLACE ".cpp" ".reduction.simd.unit" EXECUTABLE "${EXAMPLE}")
  STRING(REGEX REPLACE ".cpp" "-reduction.simd.unit" TEST "${EXAMPLE}")

  ############################################################################
  ## Add as a target
  ############################################################################
  ADD_EXECUTABLE(${EXECUTABLE} ${EXAMPLE})
  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)
  SET_TARGET_PROPERTIES(${EXECUTABLE} PROPERTIES COMPILE_FLAGS ${NT2_CXX_SIMD_FLAGS})
  ADD_DEPENDENCIES(reduction.simd.unit ${EXECUTABLE})
  ADD_TEST(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})
ENDFOREACH()