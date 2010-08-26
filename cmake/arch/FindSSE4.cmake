################################################################################
#         Copyright 2004 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8624 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Check for SSE4.1 availability
################################################################################
IF( NOT NT2_HAS_SSE4_1_SUPPORT)
TRY_RUN(RUN_RESULT_VAR COMPILE_RESULT_VAR
        ${CMAKE_MODULE_PATH}
        ${CMAKE_MODULE_PATH}/src/cpuid.cpp
        CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${NT2_CURRENT_FLAGS}
        OUTPUT_VARIABLE LOG
        ARGS sse4.1
       )

################################################################################
# If file compiles and run, we're set
################################################################################
IF(${COMPILE_RESULT_VAR})
IF( ${RUN_RESULT_VAR} MATCHES "FAILED_TO_RUN")
  set(SSE41_FOUND FALSE)
ELSE()
  set(SSE41_FOUND ${RUN_RESULT_VAR})
ENDIF()
ELSE()
  set(SSE41_FOUND FALSE)
ENDIF()

IF( ${SSE41_FOUND} )
MESSAGE( STATUS "SSE4.1 available")
ELSE()
MESSAGE( STATUS "SSE4.1 not available")
ENDIF()

ENDIF()

################################################################################
# Check for SSE4.2 availability
################################################################################
IF( NOT NT2_HAS_SSE4_2_SUPPORT)
TRY_RUN(RUN_RESULT_VAR COMPILE_RESULT_VAR
        ${CMAKE_MODULE_PATH}
        ${CMAKE_MODULE_PATH}/src/cpuid.cpp
        CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${NT2_CURRENT_FLAGS}
        OUTPUT_VARIABLE LOG
        ARGS sse4.2
       )

################################################################################
# If file compiles and run, we're set
################################################################################
IF(${COMPILE_RESULT_VAR})
IF( ${RUN_RESULT_VAR} MATCHES "FAILED_TO_RUN")
  set(SSE42_FOUND FALSE)
ELSE()
  set(SSE42_FOUND ${RUN_RESULT_VAR})
ENDIF()
ELSE()
  set(SSE42_FOUND FALSE)
ENDIF()

IF( ${SSE42_FOUND} )
MESSAGE( STATUS "SSE4.2 available")
ELSE()
MESSAGE( STATUS "SSE4.2 not available")
ENDIF()

ENDIF()
