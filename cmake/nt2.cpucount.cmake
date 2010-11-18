################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Find Number of cores
################################################################################

################################################################################
# MAC OS X use sysctl
################################################################################
IF(APPLE)
EXECUTE_PROCESS(COMMAND sysctl -n hw.ncpu
                OUTPUT_VARIABLE TMP_CPU_COUNT
               )
STRING(REGEX REPLACE "\n" "" NT2_CONFIG_CPU_COUNT ${TMP_CPU_COUNT})
ENDIF()

################################################################################
# Unix use getconf
################################################################################
IF(UNIX)
EXECUTE_PROCESS(COMMAND getconf _NPROCESSORS_ONLN
                OUTPUT_VARIABLE TMP_CPU_COUNT
               )
STRING(REGEX REPLACE "\n" "" NT2_CONFIG_CPU_COUNT ${TMP_CPU_COUNT})
ENDIF()

################################################################################
# Windows use a small cpp source
################################################################################
IF(WIN32)
################################################################################
# Compile a small cpu counter program then run it
################################################################################
TRY_RUN(RUN_RESULT_VAR COMPILE_RESULT_VAR
        ${CMAKE_MODULE_PATH}
        ${CMAKE_MODULE_PATH}/src/win32_cpucount.cpp
        CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${NT2_CURRENT_FLAGS}
       )

IF(${COMPILE_RESULT_VAR} STREQUAL "TRUE")
  SET(NT2_CONFIG_CPU_COUNT ${RUN_RESULT_VAR})
ENDIF()

ENDIF()

MESSAGE( STATUS "Cores found: ${NT2_CONFIG_CPU_COUNT}")
