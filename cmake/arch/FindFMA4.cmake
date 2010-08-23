################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Check for FMA4 availability
################################################################################

TRY_RUN(RUN_RESULT_VAR COMPILE_RESULT_VAR
        ${CMAKE_MODULE_PATH}
        ${CMAKE_MODULE_PATH}/src/cpuid.cpp
        CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${NT2_CURRENT_FLAGS}
        OUTPUT_VARIABLE LOG
        ARGS fma4
       )

################################################################################
# If file compiles and run, we're set
################################################################################
IF(${COMPILE_RESULT_VAR})
IF( ${RUN_RESULT_VAR} MATCHES "FAILED_TO_RUN")
  message(STATUS "FMA4 not available")
  set(FMA4_FOUND FALSE)
ELSE()
  set(FMA4_FOUND ${RUN_RESULT_VAR})
ENDIF()
ELSE()
  message(STATUS "FMA4 not available")
  set(FMA4_FOUND FALSE)
ENDIF()

IF( ${FMA4_FOUND} )
MESSAGE( STATUS "FMA4 available")
ELSE()
MESSAGE( STATUS "FMA4 not available")
ENDIF()

################################################################################
# Advance current test
################################################################################
mark_as_advanced(FMA4_FOUND)

