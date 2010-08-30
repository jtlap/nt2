################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Find cache size and cache line size
################################################################################
IF(NT2_PLATFORM_OSX)
 EXECUTE_PROCESS(COMMAND sysctl -n hw.cachelinesize
                 OUTPUT_VARIABLE TMP_ALIGNMENT
                )
 STRING(REGEX REPLACE "\n" "" NT2_CONFIG_ALIGNMENT ${TMP_ALIGNMENT})
ENDIF()

IF(NT2_PLATFORM_WIN32 OR NT2_PLATFORM_UNIX)
  TRY_RUN(RUN_RESULT_VAR COMPILE_RESULT_VAR
          ${CMAKE_MODULE_PATH}
          ${CMAKE_MODULE_PATH}/src/cache.cpp
         )
  SET( NT2_CONFIG_ALIGNMENT ${RUN_RESULT_VAR} )
ENDIF()

MESSAGE( STATUS "Cache line size: " ${NT2_CONFIG_ALIGNMENT} )

