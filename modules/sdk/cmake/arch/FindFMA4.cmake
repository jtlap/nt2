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
IF( NOT NT2_HAS_FMA4_SUPPORT)
FIND_FILE(SRC_CPUID src/cpuid.cpp ${CMAKE_MODULE_PATH} NO_DEFAULT_PATH)
TRY_RUN(RUN_RESULT_VAR COMPILE_RESULT_VAR
        ${PROJECT_BINARY_DIR}/cmake
        ${SRC_CPUID}
        CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${NT2_CURRENT_FLAGS}
        OUTPUT_VARIABLE LOG
        ARGS fma4
       )

################################################################################
# If file compiles and run, we're set
################################################################################
IF(COMPILE_RESULT_VAR STREQUAL TRUE)
IF( ${RUN_RESULT_VAR} MATCHES "FAILED_TO_RUN")
  set(FMA4_FOUND 0)
ELSE()
  set(FMA4_FOUND ${RUN_RESULT_VAR})
ENDIF()
ELSE()
  set(FMA4_FOUND 0)
ENDIF()

IF( ${FMA4_FOUND} )
MESSAGE( STATUS "FMA4 available")
################################################################################
# Find the proper options to compile
################################################################################
check_cxx_compiler_flag("-mfma4" HAS_GCC_FMA4)
check_cxx_compiler_flag("/arch:fma4" HAS_MSVC_FMA4)

IF(HAS_GCC_FMA4)
set(NT2_SIMD_FLAGS "${NT2_SIMD_FLAGS} -mfma4")
ENDIF()

IF(HAS_MSVC_FMA4)
set(NT2_SIMD_FLAGS "${NT2_SIMD_FLAGS} /arch:fma4")
ENDIF()
################################################################################

ELSE()
MESSAGE( STATUS "FMA4 not available")
ENDIF()

ENDIF()
