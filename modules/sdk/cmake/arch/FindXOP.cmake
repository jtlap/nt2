################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Check for XOP availability
################################################################################
IF( NOT NT2_HAS_XOP_SUPPORT)
FIND_FILE(SRC_CPUID src/cpuid.cpp ${CMAKE_MODULE_PATH} NO_DEFAULT_PATH)
TRY_RUN(RUN_RESULT_VAR COMPILE_RESULT_VAR
        ${PROJECT_BINARY_DIR}/cmake
        ${SRC_CPUID}
        CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${NT2_CURRENT_FLAGS}
        OUTPUT_VARIABLE LOG
        ARGS xop
       )

################################################################################
# If file compiles and run, we're set
################################################################################
IF(COMPILE_RESULT_VAR STREQUAL TRUE)
IF( ${RUN_RESULT_VAR} MATCHES "FAILED_TO_RUN")
  set(XOP_FOUND 0)
ELSE()
  set(XOP_FOUND ${RUN_RESULT_VAR})
ENDIF()
ELSE()
  set(XOP_FOUND 0)
ENDIF()

IF( ${XOP_FOUND} )
MESSAGE( STATUS "XOP available")
################################################################################
# Find the proper options
################################################################################
check_cxx_compiler_flag("-mxop" HAS_GCC_XOP)
check_cxx_compiler_flag("/arch:xop" HAS_MSVC_XOP)

IF(HAS_GCC_SSE2)
set(NT2_SIMD_FLAGS "-mxop")
ENDIF()

IF(HAS_MSVC_SSE2)
set(NT2_SIMD_FLAGS "/arch:xop")
ENDIF()
################################################################################

ELSE()
MESSAGE( STATUS "XOP not available")
ENDIF()

ENDIF()
