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
    cardinal_of.cpp
    category_of.cpp
    gcd.cpp
    is_result_of_supported.cpp
    is_scalar.cpp
    scalar_of.cpp
    set.cpp
   )

#####
# TODO:
# *adapted_traits.cpp
# *behave_as.cpp
# lcm.cpp
#####

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
