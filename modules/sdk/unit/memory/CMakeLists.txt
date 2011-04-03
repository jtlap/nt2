################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

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
    allocator_adaptor.cpp
    buffer.cpp
    slice.cpp
    stride.cpp
    #block1D.cpp
  )

ADD_CUSTOM_TARGET(sdk.memory.unit)
ADD_DEPENDENCIES(sdk.unit sdk.memory.unit)

################################################################################
# For each filename
################################################################################
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_unit(sdk.memory.${EXAMPLE}.unit ${EXAMPLE}.cpp)
ENDFOREACH()
