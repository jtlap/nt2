################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

# avoid re-checking every time
if(DEFINED OpenMP_CXX_FLAGS AND NOT OpenMP_CXX_FLAGS)
  set(OPENMP_FOUND 0)
else()
  find_package(OpenMP QUIET)
endif()

set(NT2_ARCH.OPENMP_DEPENDENCIES_FOUND ${OPENMP_FOUND})
set(NT2_ARCH.OPENMP_COMPILE_FLAGS ${OpenMP_CXX_FLAGS})
if(NOT MSVC)
  set(NT2_ARCH.OPENMP_LINK_FLAGS ${OpenMP_CXX_FLAGS})
endif()
set(NT2_ARCH.OPENMP_DEPENDENCIES_EXTRA core.utility)
