##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  is_nle.cpp
  is_nge.cpp
  is_nlt.cpp
  is_ngt.cpp
  is_not_infinite.cpp
  majority.cpp
  sb2b.cpp
  is_unord.cpp
  is_true.cpp
  is_positive.cpp
  is_ord.cpp
  is_odd.cpp
  is_not_finite.cpp
  is_nltz.cpp
  is_nlez.cpp
  is_ngtz.cpp
  is_ngez.cpp
  is_nez.cpp
  is_negative.cpp
  is_nan.cpp
  is_ltz.cpp
  is_lez.cpp
  is_invalid.cpp
  is_inf.cpp
  is_gtz.cpp
  is_gez.cpp
  is_flint.cpp
  is_finite.cpp
  is_false.cpp
  is_even.cpp
  is_eqz.cpp
  boolean.cpp
# List of simd test files for toolbox predicates
   )

##############################################################################
# For each filename
##############################################################################
FOREACH( EXAMPLE ${SOURCES})
  ############################################################################
  ## Build the executable filename from the example source filename
  ############################################################################
  STRING(REGEX REPLACE ".cpp" ".predicates.simd.unit" EXECUTABLE "${EXAMPLE}")
  STRING(REGEX REPLACE ".cpp" "-predicates.simd.unit" TEST "${EXAMPLE}")

  ############################################################################
  ## Add as a target
  ############################################################################
  ADD_EXECUTABLE(${EXECUTABLE} ${EXAMPLE})
  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)
  SET_TARGET_PROPERTIES(${EXECUTABLE} PROPERTIES COMPILE_FLAGS ${NT2_CXX_SIMD_FLAGS})
  ADD_DEPENDENCIES(predicates.simd.unit ${EXECUTABLE})
  ADD_TEST(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})
ENDFOREACH()
