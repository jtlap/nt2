################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Check for MMX availability
################################################################################

TRY_RUN(RUN_RESULT_VAR COMPILE_RESULT_VAR
        ${CMAKE_MODULE_PATH}
        ${CMAKE_MODULE_PATH}/src/cpuid.cpp
        CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${NT2_CURRENT_FLAGS}
        ARGS mmx
       )


################################################################################
# If file compiles and run, we're set
################################################################################
IF(${COMPILE_RESULT_VAR})
IF( ${RUN_RESULT_VAR} MATCHES "FAILED_TO_RUN")
  set(MMX_FOUND FALSE)
ELSE()
  set(MMX_FOUND ${RUN_RESULT_VAR})
ENDIF()
ELSE()
  set(MMX_FOUND FALSE)
ENDIF()

IF( ${MMX_FOUND} )
MESSAGE( STATUS "MMX available")
ELSE()
MESSAGE( STATUS "MMX not available")
ENDIF()

################################################################################
# Advance current test
################################################################################
mark_as_advanced(MMX_FOUND)

