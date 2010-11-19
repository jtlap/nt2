################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/)

SET( SOURCES
    is_power_of_2.cpp
    next_power_of_2.cpp
    align_on.cpp
    is_aligned.cpp
    make_aligned.cpp
    access.cpp
    allocate.cpp
    overload.cpp
    allocator.cpp
    dynamic_buffer.cpp
    dynamic_static_buffer.cpp
    static_dynamic_buffer.cpp
    static_buffer.cpp
    slice.cpp
    stride.cpp
    block1D.cpp
  )

ADD_CUSTOM_TARGET(sdk.memory.unit)
ADD_DEPENDENCIES(sdk.unit sdk.memory.unit)

################################################################################
# For each filename
################################################################################
FOREACH( EXAMPLE ${SOURCES})
  ##############################################################################
  # Build the executable filename from the example source filename
  ##############################################################################
  STRING(REGEX REPLACE ".cpp" ".unit" EXECUTABLE "${EXAMPLE}")
  STRING(REGEX REPLACE ".cpp" "-unit" TEST "${EXAMPLE}")

  ##############################################################################
  # Add as a target
  ##############################################################################
  ADD_EXECUTABLE(${EXECUTABLE} ${EXAMPLE})
  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)
  ADD_TEST(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})
  ADD_DEPENDENCIES(sdk.memory.unit ${EXECUTABLE})
ENDFOREACH()
