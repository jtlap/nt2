################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
    any.cpp
    as_integer.cpp
    as_bits.cpp
    as_real.cpp
    cardinal_of.cpp
    category_of.cpp
    from_bits.cpp
    is_result_of_supported.cpp
    is_scalar.cpp
    is_signed.cpp
    make_integer.cpp
    make_real.cpp
    scalar_of.cpp
    set.cpp
    sign_of.cpp
    strip.cpp
   )

include_directories( ${PROJECT_SOURCE_DIR}/)

################################################################################
# For each filename
################################################################################
FOREACH( EXAMPLE ${SOURCES})
  ##############################################################################
  # Build the executable filename from the example source filename
  ##############################################################################
  STRING(REGEX REPLACE ".cpp" ".test" EXECUTABLE "${EXAMPLE}")
  STRING(REGEX REPLACE ".cpp" "-test" TEST "${EXAMPLE}")

  ##############################################################################
  # Add as a target
  ##############################################################################
  ADD_EXECUTABLE(${EXECUTABLE} ${EXAMPLE})
  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)
  ADD_TEST(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})
ENDFOREACH()
