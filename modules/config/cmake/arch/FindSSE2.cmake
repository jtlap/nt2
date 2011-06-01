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
FIND_FILE(SRC_CPUID src/cpuid.cpp ${CMAKE_MODULE_PATH} NO_DEFAULT_PATH)
TRY_RUN(RUN_RESULT_VAR COMPILE_RESULT_VAR
        ${PROJECT_BINARY_DIR}/cmake
        ${SRC_CPUID}
        CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${NT2_CURRENT_FLAGS}
        OUTPUT_VARIABLE LOG
        ARGS sse2
       )

################################################################################
# If file compiles and run, we're set
################################################################################
IF(COMPILE_RESULT_VAR STREQUAL TRUE)
IF( ${RUN_RESULT_VAR} MATCHES "FAILED_TO_RUN")
  set(SSE2_FOUND 0)
ELSE()
  set(SSE2_FOUND ${RUN_RESULT_VAR})
ENDIF()
ELSE()
  set(SSE2_FOUND 0)
ENDIF()

IF( ${SSE2_FOUND} )
MESSAGE( STATUS "SSE2 available")

################################################################################
# Find the proper options to compile SSE2 here
################################################################################
check_cxx_compiler_flag("-msse2" HAS_GCC_SSE2)
check_cxx_compiler_flag("/arch:SSE2" HAS_MSVC_SSE2)

IF(HAS_GCC_SSE2)
set(NT2_SIMD_FLAGS "${NT2_SIMD_FLAGS} -msse2")
ENDIF()

IF(HAS_MSVC_SSE2)
set(NT2_SIMD_FLAGS "${NT2_SIMD_FLAGS} /arch:SSE2")
ENDIF()
################################################################################

ELSE()
MESSAGE( STATUS "SSE2 not available")
ENDIF()

ENDIF()
