################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Check for SSE2 availability
################################################################################
IF( NOT NT2_HAS_SSE2_SUPPORT)
TRY_RUN(RUN_RESULT_VAR COMPILE_RESULT_VAR
        ${CMAKE_MODULE_PATH}
        ${CMAKE_MODULE_PATH}/src/cpuid.cpp
        CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${NT2_CURRENT_FLAGS}
        OUTPUT_VARIABLE LOG
        ARGS sse2
       )

################################################################################
# If file compiles and run, we're set
################################################################################
IF(${COMPILE_RESULT_VAR})
IF( ${RUN_RESULT_VAR} MATCHES "FAILED_TO_RUN")
  set(SSE2_FOUND FALSE)
ELSE()
  set(SSE2_FOUND ${RUN_RESULT_VAR})
ENDIF()
ELSE()
  set(SSE2_FOUND FALSE)
ENDIF()

IF( ${SSE2_FOUND} )
MESSAGE( STATUS "SSE2 available")
ELSE()
MESSAGE( STATUS "SSE2 not available")
ENDIF()

ENDIF()
