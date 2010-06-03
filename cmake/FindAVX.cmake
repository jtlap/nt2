################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Check for AVX extensions availability
################################################################################

try_run(AVX_RUN_RESULT_VAR AVX_COMPILE_RESULT_VAR
        ${CMAKE_BINARY_DIR} 
        ${CMAKE_MODULE_PATH}/has_avx.cpp
        CMAKE_FLAGS 
          -DCOMPILE_DEFINITIONS:STRING=-mAVX
       )

IF(${AVX_COMPILE_RESULT_VAR})
IF( ${AVX_RUN_RESULT_VAR} MATCHES "FAILED_TO_RUN")
  message(STATUS "AVX Extension not available")
  set(AVX_FOUND FALSE)
ELSE()
  message(STATUS "AVX Extension available")
  set(AVX_FOUND TRUE)
ENDIF()
ELSE()
  message(STATUS "AVX Extension not available")
  set(AVX_FOUND FALSE)
ENDIF()

mark_as_advanced(AVX_FOUND)

