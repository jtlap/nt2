################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

FIND_PACKAGE(NT2 COMPONENTS bitwise ieee)
SET(NT2_ARITHMETIC_DEPENDENCIES_FOUND ${NT2_FOUND})
SET(NT2_ARITHMETIC_DEPENDENCIES_INCLUDE_DIR ${NT2_INCLUDE_DIR})
SET(NT2_ARITHMETIC_DEPENDENCIES_LIBRARIES ${NT2_LIBRARIES})
SET(NT2_ARITHMETIC_DEPENDENCIES_FLAGS ${NT2_FLAGS})

IF(NOT NT2_FOUND)
  RETURN()
ENDIF()

FIND_PACKAGE(PythonInterp)
IF(NOT PYTHONINTERP_FOUND)
  SET(NT2_ARITHMETIC_DEPENDENCIES_FOUND 0)
  RETURN()
ENDIF()

FIND_FILE(SIMD_FWD_PY simd_fwd.py ${CMAKE_MODULE_PATH} NO_DEFAULT_PATH)
EXECUTE_PROCESS( COMMAND ${PYTHON_EXECUTABLE}
                 ${SIMD_FWD_PY}
                 ${NT2_ARITHMETIC_ROOT}/include ${PROJECT_BINARY_DIR}/include
                 nt2/toolbox/arithmetic/function
               )
