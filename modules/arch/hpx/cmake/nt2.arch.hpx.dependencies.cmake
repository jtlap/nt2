################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

# avoid re-checking every time
if(DEFINED HPX_CXX_FLAGS AND NOT HPX_CXX_FLAGS)
  set(HPX_FOUND 0)
else()
  find_package(PkgConfig)
  pkg_check_modules(HPX_VARIABLE REQUIRED hpx_application)
  if(HPX_VARIABLE_FOUND)
    set(HPX_CXX_FLAGS "-DNT2_USE_HPX")
    set(HPX_FOUND 1)
    foreach(tmp ${HPX_VARIABLE_CFLAGS})
      set(HPX_CXX_FLAGS "${HPX_CXX_FLAGS} ${tmp}")
    endforeach()
  endif ()
endif()

set(NT2_ARCH.HPX_DEPENDENCIES_FOUND ${HPX_FOUND})
set(NT2_ARCH.HPX_COMPILE_FLAGS ${HPX_CXX_FLAGS})
set(NT2_ARCH.HPX_DEPENDENCIES_INCLUDE_DIR ${HPX_VARIABLE_INCLUDE_DIRS})
set(NT2_ARCH.HPX_DEPENDENCIES_LIBRARY_DIR ${HPX_VARIABLE_LIBRARY_DIRS})
set(NT2_ARCH.HPX_DEPENDENCIES_LIBRARIES   ${HPX_VARIABLE_LIBRARIES})

set ( NT2_ARCH.HPX_DEPENDENCIES_EXTRA
      arch.shared_memory
      boost.dispatch
      sdk.functor
    )
