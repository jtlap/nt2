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
    aligned_object.cpp
    allocate.cpp
    allocator.cpp
    allocator_adaptor.cpp
    is_aligned.cpp
    is_power_of_2.cpp
    make_aligned.cpp
    next_power_of_2.cpp
    prev_power_of_2.cpp
    overload.cpp
    new.cpp
    range.cpp
    stack_buffer.cpp
  )

nt2_module_add_tests(boost.simd.memory.sdk.unit ${SOURCES})
