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
IF(APPLE)
 execute_process(COMMAND sysctl -n hw.cachelinesize
                 OUTPUT_VARIABLE TMP_ALIGNMENT
                )
 STRING(REGEX REPLACE "\n" "" NT2_CONFIG_ALIGNMENT ${TMP_ALIGNMENT})
ELSE()
 # APPLE also seems to count as UNIX, so putting it into else branch
 IF(UNIX OR WIN32)
  try_run(RUN_RESULT_VAR COMPILE_RESULT_VAR
          ${CMAKE_MODULE_PATH}
          ${CMAKE_MODULE_PATH}/src/cache.cpp
         )
  SET( NT2_CONFIG_ALIGNMENT ${RUN_RESULT_VAR} )
 ENDIF()
ENDIF()

MESSAGE( STATUS "Cache line size: " ${NT2_CONFIG_ALIGNMENT} )

