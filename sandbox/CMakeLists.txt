################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Some global random test
################################################################################
FIND_PACKAGE(NT2 COMPONENTS sdk)
INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR}/include ${NT2_INCLUDE_DIR})
LINK_DIRECTORIES(${NT2_LIBRARY_DIR})
LINK_LIBRARIES(${NT2_LIBRARIES})
SET(SOURCES
pack.cpp
#    foo.cpp
#table_dim.cpp
    )

ADD_CUSTOM_TARGET(sandbox)

################################################################################
# For each filename
################################################################################
FOREACH( EXAMPLE ${SOURCES})
  ##############################################################################
  # Build the executable filename from the example source filename
  ##############################################################################
  STRING(REGEX REPLACE ".cpp" "" EXECUTABLE "${EXAMPLE}")

  ##############################################################################
  # Add as a target
  ##############################################################################
  ADD_EXECUTABLE(${EXECUTABLE} EXCLUDE_FROM_ALL ${EXAMPLE})
  IF(NT2_FLAGS)
    SET_TARGET_PROPERTIES(${EXECUTABLE} PROPERTIES COMPILE_FLAGS ${NT2_FLAGS})
  ENDIF()
  ADD_DEPENDENCIES(sandbox ${EXECUTABLE})
ENDFOREACH()

