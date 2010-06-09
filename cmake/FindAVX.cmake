################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Check for AVX availability
################################################################################

################################################################################
# Set proper flag setter depending on compiler
################################################################################
IF(CMAKE_COMPILER_IS_GNUCXX)
SET(SIMD_FLAGS -mavx)
ENDIF()

IF(CMAKE_COMPILER_IS_MSVC)
SET(SIMD_FLAGS \arch:AVX)
ENDIF()

################################################################################
# Try to compile and run said file
################################################################################
try_run(RUN_RESULT_VAR COMPILE_RESULT_VAR
        ${CMAKE_MODULE_PATH}
        ${CMAKE_MODULE_PATH}/avx.cpp
        CMAKE_FLAGS
          -DCOMPILE_DEFINITIONS:STRING=${SIMD_FLAGS}
       )

################################################################################
# If file compiles and run, we're set
################################################################################
IF(${COMPILE_RESULT_VAR})
IF( ${RUN_RESULT_VAR} MATCHES "FAILED_TO_RUN")
  message(STATUS "AVX not available")
  set(AVX_FOUND FALSE)
ELSE()
  message(STATUS "AVX available")
  set(AVX_FOUND TRUE)
ENDIF()
ELSE()
  message(STATUS "AVX not available")
  set(AVX_FOUND FALSE)
ENDIF()

################################################################################
# Advance current test
################################################################################
mark_as_advanced(AVX_FOUND)

