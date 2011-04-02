################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Check for AVX availability
################################################################################
IF( NOT NT2_HAS_AVX_SUPPORT)
FIND_FILE(SRC_CPUID src/cpuid.cpp ${CMAKE_MODULE_PATH} NO_DEFAULT_PATH)
TRY_RUN(RUN_RESULT_VAR COMPILE_RESULT_VAR
        ${PROJECT_BINARY_DIR}/cmake
        ${SRC_CPUID}
        CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${NT2_CURRENT_FLAGS}
        OUTPUT_VARIABLE LOG
        ARGS avx
       )

################################################################################
# If file compiles and run, we're set
################################################################################
IF(COMPILE_RESULT_VAR STREQUAL TRUE)
IF( ${RUN_RESULT_VAR} MATCHES "FAILED_TO_RUN")
  set(AVX_FOUND 0)
ELSE()
  set(AVX_FOUND ${RUN_RESULT_VAR})
ENDIF()
ELSE()
  set(AVX_FOUND 0)
ENDIF()

IF( ${AVX_FOUND} )
MESSAGE( STATUS "AVX available")

################################################################################
# Find the proper options
################################################################################
check_cxx_compiler_flag("-mavx" HAS_GCC_AVX)
check_cxx_compiler_flag("/arch:avx" HAS_MSVC_AVX)

IF(HAS_GCC_SSE2)
set(NT2_SIMD_FLAGS "-mavx")
ENDIF()

IF(HAS_MSVC_SSE2)
set(NT2_SIMD_FLAGS "/arch:avx")
ENDIF()
################################################################################

ELSE()
MESSAGE( STATUS "AVX not available")
ENDIF()

ENDIF()
