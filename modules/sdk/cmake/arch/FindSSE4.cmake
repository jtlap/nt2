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
FIND_FILE(SRC_CPUID src/cpuid.cpp ${CMAKE_MODULE_PATH} NO_DEFAULT_PATH)
TRY_RUN(RUN_RESULT_VAR COMPILE_RESULT_VAR
        ${PROJECT_BINARY_DIR}/cmake
        ${SRC_CPUID}
        CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${NT2_CURRENT_FLAGS}
        OUTPUT_VARIABLE LOG
        ARGS sse4.1
       )

################################################################################
# If file compiles and run, we're set
################################################################################
IF(COMPILE_RESULT_VAR STREQUAL TRUE)
IF( ${RUN_RESULT_VAR} MATCHES "FAILED_TO_RUN")
  set(SSE41_FOUND 0)
ELSE()
  set(SSE41_FOUND ${RUN_RESULT_VAR})
ENDIF()
ELSE()
  set(SSE41_FOUND 0)
ENDIF()

IF( ${SSE41_FOUND} )
MESSAGE( STATUS "SSE4.1 available")
################################################################################
# Find the proper options to compile
################################################################################
check_cxx_compiler_flag("-msse4.1" HAS_GCC_SSE41)
check_cxx_compiler_flag("/arch:SSE4.1" HAS_MSVC_SSE41)

IF(HAS_GCC_SSE41)
set(NT2_SIMD_FLAGS "${NT2_SIMD_FLAGS} -msse4.1")
ENDIF()

IF(HAS_MSVC_SSE41)
set(NT2_SIMD_FLAGS "${NT2_SIMD_FLAGS} /arch:SSE4.1")
ENDIF()
################################################################################

ELSE()
MESSAGE( STATUS "SSE4.1 not available")
ENDIF()

ENDIF()

################################################################################
# Check for SSE4.2 availability
################################################################################
IF( NOT NT2_HAS_SSE4_2_SUPPORT)
FIND_FILE(SRC_CPUID src/cpuid.cpp ${CMAKE_MODULE_PATH} NO_DEFAULT_PATH)
TRY_RUN(RUN_RESULT_VAR COMPILE_RESULT_VAR
        ${PROJECT_BINARY_DIR}/cmake
        ${SRC_CPUID}
        CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${NT2_CURRENT_FLAGS}
        OUTPUT_VARIABLE LOG
        ARGS sse4.2
       )

################################################################################
# If file compiles and run, we're set
################################################################################
IF(COMPILE_RESULT_VAR)
IF( ${RUN_RESULT_VAR} MATCHES "FAILED_TO_RUN")
  set(SSE42_FOUND 0)
ELSE()
  set(SSE42_FOUND ${RUN_RESULT_VAR})
ENDIF()
ELSE()
  set(SSE42_FOUND 0)
ENDIF()

IF( ${SSE42_FOUND} )
MESSAGE( STATUS "SSE4.2 available")
################################################################################
# Find the proper options to compile
################################################################################
check_cxx_compiler_flag("-msse4.2" HAS_GCC_SSE42)
check_cxx_compiler_flag("/arch:SSE4.2" HAS_MSVC_SSE42)

IF(HAS_GCC_SSE42)
set(NT2_SIMD_FLAGS "${NT2_SIMD_FLAGS} -msse4.2")
ENDIF()

IF(HAS_MSVC_SSE42)
set(NT2_SIMD_FLAGS "${NT2_SIMD_FLAGS} /arch:SSE4.2")
ENDIF()
################################################################################

ELSE()
MESSAGE( STATUS "SSE4.2 not available")
ENDIF()

ENDIF()
