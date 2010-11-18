################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
#    native.cpp
    as_integer.cpp
    as_real.cpp
    as_signed.cpp
    as_unsigned.cpp
    cardinal_of.cpp
    category_of.cpp
    is_signed.cpp
    make_integer.cpp
    make_real.cpp
    scalar_of.cpp
    sign_of.cpp
    access.cpp
    native_cast.cpp
#    pack.cpp
#    add.cpp
#    sub.cpp
#    div.cpp
#    mul.cpp
#    eq.cpp
#    neq.cpp
#    lt.cpp
#    gt.cpp
#    le.cpp
#    ge.cpp
   )

include_directories( ${PROJECT_SOURCE_DIR}/)

ADD_CUSTOM_TARGET(sdk.simd.unit)
ADD_DEPENDENCIES(sdk.unit sdk.simd.unit)

################################################################################
# For each filename
################################################################################
FOREACH( EXAMPLE ${SOURCES})
  ##############################################################################
  # Build the executable filename from the example source filename
  ##############################################################################
  STRING(REGEX REPLACE ".cpp" ".simd.unit" EXECUTABLE "${EXAMPLE}")
  STRING(REGEX REPLACE ".cpp" "-simd.unit" TEST "${EXAMPLE}")

  ##############################################################################
  # Add as a target
  ##############################################################################
  ADD_EXECUTABLE(${EXECUTABLE} ${EXAMPLE})
  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)
  SET_TARGET_PROPERTIES(${EXECUTABLE} PROPERTIES COMPILE_FLAGS ${NT2_CXX_SIMD_FLAGS})
  ADD_TEST(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})
  ADD_DEPENDENCIES(sdk.simd.unit ${EXECUTABLE})
ENDFOREACH()
