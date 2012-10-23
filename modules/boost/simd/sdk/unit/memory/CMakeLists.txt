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
    allocate.cpp
    overload.cpp
    allocator.cpp
    allocator_adaptor.cpp
    aligned_array.cpp
  )

nt2_module_add_tests(boost.simd.sdk.memory.unit ${SOURCES})
