################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Check for SIMD extensions availability
################################################################################

################################################################################
# Set proper flag setter depending on compiler
################################################################################
IF(CMAKE_COMPILER_IS_GNUCXX)
SET(SIMD_OPT -m)
ENDIF()

IF(CMAKE_COMPILER_IS_MSVC)
SET(SIMD_OPT \arch:)
ENDIF()

################################################################################
# Write the test file
################################################################################
file(WRITE ${CMAKE_BINARY_DIR}/find.cpp
     "#include <${SIMD_INCLUDE}>\n"
     "int main() {\n" 
     "  ${SIMD_TYPE} x;\n"
     "  x = ${SIMD_OP}(x,x);\n"
     "  return 1; }\n" 
     )

################################################################################
# Try to compile and run said file
################################################################################
try_run(RUN_RESULT_VAR COMPILE_RESULT_VAR
        ${CMAKE_BINARY_DIR} 
        ${CMAKE_BINARY_DIR}/find.cpp
        CMAKE_FLAGS 
          -DCOMPILE_DEFINITIONS:STRING=${SIMD_OPT}${SIMD_FLAGS}
       )

################################################################################
# If file compiles and run, we're set
################################################################################
IF(${COMPILE_RESULT_VAR})
IF( ${RUN_RESULT_VAR} MATCHES "FAILED_TO_RUN")
  message(STATUS "${SIMD_FLAGS} not available")
  set(${SIMD_VAR} FALSE)
ELSE()
  message(STATUS "${SIMD_FLAGS} available")
  set(${SIMD_VAR} TRUE)
ENDIF()
ELSE()
  message(STATUS "${SIMD_FLAGS} not available")
  set(${SIMD_VAR} FALSE)
ENDIF()

################################################################################
# Advacne current test
################################################################################
mark_as_advanced(${SIMD_VAR})

