################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET(  SOURCES
      align_on.cpp
      align_on_c.cpp
      align_ptr.cpp
      is_aligned.cpp
      is_aligned_c.cpp
      is_power_of_2.cpp
      is_power_of_2_c.cpp
      prev_power_of_2.cpp
      prev_power_of_2_c.cpp
      next_power_of_2.cpp
      next_power_of_2_c.cpp
)

################################################################################
# For each filename
################################################################################
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_example(boost.simd.sdk.memory.meta.${EXAMPLE}.sample ${EXAMPLE}.cpp)
ENDFOREACH()
