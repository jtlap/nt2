################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{HPX_ROOT}/share/cmake-2.8/Modules")

# avoid re-checking every time
if(DEFINED HPX_CXX_FLAGS AND NOT HPX_CXX_FLAGS)
  set(HPX_FOUND 0)
else()
  find_package(HPX QUIET)
  if (HPX_FOUND)
    message(STATUS "HPX was found.")
    set(HPX_CXX_FLAGS "-DNT2_USE_HPX ${HPX_CXX_COMPILE_FLAGS}")
  endif (HPX_FOUND)
endif()

set(NT2_ARCH.HPX_DEPENDENCIES_FOUND ${HPX_FOUND})
set(NT2_ARCH.HPX_COMPILE_FLAGS ${HPX_CXX_FLAGS})
set(NT2_ARCH.HPX_DEPENDENCIES_INCLUDE_DIR ${HPX_INCLUDE_DIR})
set(NT2_ARCH.HPX_DEPENDENCIES_LIBRARY_DIR ${HPX_LIBRARY_DIR})
set(NT2_ARCH.HPX_DEPENDENCIES_LIBRARIES   ${HPX_LIBRARIES})

set ( NT2_ARCH.HPX_DEPENDENCIES_EXTRA
      arch.shared_memory
      boost.dispatch
      sdk.functor
    )
