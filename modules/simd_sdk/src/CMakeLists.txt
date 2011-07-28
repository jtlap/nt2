################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(sdk)

set(SOURCES
    details/timestamp.cpp
    error/assert_exception.cpp
    error/exception.cpp
    memory/allocate.cpp
    memory/deallocate.cpp
    memory/reallocate.cpp
    timing/now.cpp
    timing/timers.cpp
    config/version.cpp
   )
nt2_module_add_library(boost_simd ${SOURCES})
