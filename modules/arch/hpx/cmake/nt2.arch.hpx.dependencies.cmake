################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

if(NOT DEFINED HPX_ROOT)
  set(HPX_ROOT $ENV{HPX_ROOT})
endif()
find_path(HPX_INCLUDE_DIR hpx/hpx.hpp PATHS HPX_ROOT)
find_library(HPX_LIBRARY hpx PATHS HPX_ROOT/lib PATH_SUFFIXES hpx)

if(NOT HPX_INCLUDE_DIR OR NOT HPX_LIBRARY)
  set(NT2_ARCH.HPX_DEPENDENCIES_FOUND 0)
endif()

set(NT2_ARCH.HPX_COMPILE_FLAGS "-DNT2_USE_HPX")
if(CMAKE_COMPILER_IS_GNUCXX)
  set(NT2_ARCH.HPX_COMPILE_FLAGS "${NT2_ARCH.HPX_COMPILE_FLAGS} -std=c++0x")
endif()

set(NT2_ARCH.HPX_DEPENDENCIES_INCLUDE_DIR ${HPX_INCLUDE_DIR} ${HPX_INCLUDE_DIR}/hpx/external)
set(NT2_ARCH.HPX_DEPENDENCIES_LIBRARIES   ${HPX_LIBRARY})

set( NT2_ARCH.HPX_DEPENDENCIES_EXTRA
     arch.shared_memory
     boost.dispatch
     sdk.functor
   )
