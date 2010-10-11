##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  group.cpp
  splatted_second.cpp
  comparator.cpp
  lookup.cpp
  sort.cpp
  cumsum.cpp
  split.cpp
  splatted_maximum.cpp
  splatted_minimum.cpp
  splatted_prod.cpp
  splatted_first.cpp
  splatted_sum.cpp
  put_first.cpp
# List of simd test files for toolbox swar
   )

##############################################################################
# For each filename
##############################################################################
FOREACH( EXAMPLE ${SOURCES})
  ############################################################################
  ## Build the executable filename from the example source filename
  ############################################################################
  STRING(REGEX REPLACE ".cpp" ".swar.simd.unit" EXECUTABLE "${EXAMPLE}")
  STRING(REGEX REPLACE ".cpp" "-swar.simd.unit" TEST "${EXAMPLE}")

  ############################################################################
  ## Add as a target
  ############################################################################
  ADD_EXECUTABLE(${EXECUTABLE} ${EXAMPLE})
  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)
  SET_TARGET_PROPERTIES(${EXECUTABLE} PROPERTIES COMPILE_FLAGS ${NT2_CXX_SIMD_FLAGS})
  ADD_DEPENDENCIES(swar.simd.unit ${EXECUTABLE})
  ADD_TEST(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})
ENDFOREACH()
