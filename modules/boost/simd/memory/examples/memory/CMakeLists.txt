################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET(  SOURCES
      aligned_array.cpp
      align_on.cpp
      align_on_default.cpp
      align_ptr.cpp
      aligned_object.cpp
      aligned_output_iterator.cpp
      bitwise_cast.cpp
      input_iterator.cpp
      input_range.cpp
      is_aligned.cpp
      is_power_of_2.cpp
      aligned_load.cpp
      new.cpp
      scoped_buffer.cpp
      simd_malloc.cpp
      simd_scoped_buffer.cpp
      simd_stack_buffer.cpp
      stack_buffer.cpp
      aligned_store.cpp
)

################################################################################
# For each filename
################################################################################
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_example(boost.simd.memory.${EXAMPLE}.sample ${EXAMPLE}.cpp)
ENDFOREACH()
