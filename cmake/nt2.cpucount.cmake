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

IF(UNIX)
execute_process(COMMAND getconf _NPROCESSORS_ONLN
                OUTPUT_VARIABLE NT2_CONFIG_CPU_COUNT
               )
ENDIF()

if(DARWIN)
endif(DARWIN)

IF(WINDOWS)
################################################################################
# Compile a small cpu counter program then run it
################################################################################
try_run(RUN_RESULT_VAR COMPILE_RESULT_VAR
        ${CMAKE_MODULE_PATH}
        ${CMAKE_MODULE_PATH}/cpu.cpp
       )

IF(${COMPILE_RESULT_VAR})
  message(STATUS "cpu count ${RUN_RESULT_VAR}")
  set(${NT2_CONFIG_CPU_COUNT} ${RUN_RESULT_VAR})
ENDIF()

ENDIF()
