################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
    align_on.cpp
    aligned_array.cpp
    aligned_malloc.cpp
    aligned_malloc_override.cpp
    aligned_input_iterator.cpp
    aligned_input_range.cpp
    aligned_output_iterator.cpp
    aligned_output_range.cpp
    aligned_object.cpp
    aligned_realloc.cpp
    aligned_realloc_override.cpp
    allocate.cpp
    allocator.cpp
    allocator_adaptor.cpp
    direct_output_iterator.cpp
    input_iterator.cpp
    input_range.cpp
    is_aligned.cpp
    is_power_of_2.cpp
    iterator_hierarchy.cpp
    make_aligned.cpp
    new.cpp
    next_power_of_2.cpp
    overload.cpp
    output_iterator.cpp
    output_range.cpp
    prev_power_of_2.cpp
    reallocate.cpp
    realigned_input_range.cpp
    realigned_output_range.cpp
    reuse.cpp
    shifted_iterator.cpp
    stack_buffer.cpp
  )

nt2_module_add_tests(boost.simd.sdk.memory.utility.unit ${SOURCES})
