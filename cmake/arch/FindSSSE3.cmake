################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Check for SSSE3 availability
################################################################################

TRY_RUN(RUN_RESULT_VAR COMPILE_RESULT_VAR
        ${CMAKE_MODULE_PATH}
        ${CMAKE_MODULE_PATH}/src/cpuid.cpp
        CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${NT2_CURRENT_FLAGS}
        OUTPUT_VARIABLE LOG
        ARGS ssse3
       )

################################################################################
# If file compiles and run, we're set
################################################################################
IF(${COMPILE_RESULT_VAR})
IF( ${RUN_RESULT_VAR} MATCHES "FAILED_TO_RUN")
  set(SSSE3_FOUND FALSE)
ELSE()
  set(SSSE3_FOUND ${RUN_RESULT_VAR})
ENDIF()
ELSE()
  set(SSE3_FOUND FALSE)
ENDIF()

IF( ${SSE3_FOUND} )
MESSAGE( STATUS "SSSE3 available")
ELSE()
MESSAGE( STATUS "SSSE3 not available")
ENDIF()

################################################################################
# Advance current test
################################################################################
mark_as_advanced(SSSE3_FOUND)

