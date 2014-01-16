################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(nt2.boost)
find_package(Boost 1.53.0 QUIET COMPONENTS program_options thread system serialization)

if(NOT DEFINED HPX_ROOT)
  set(HPX_ROOT $ENV{HPX_ROOT})
endif()
if(NOT DEFINED HPX_BINARY_ROOT)
  set(HPX_BINARY_ROOT $ENV{HPX_BINARY_ROOT})
endif()
find_path(HPX_INCLUDE_DIR hpx/hpx.hpp PATHS ${HPX_ROOT})
find_path(HPX_INCLUDE_BINARY_DIR hpx/config/defines.hpp PATHS ${HPX_BINARY_ROOT} ${HPX_ROOT})

if(HPX_ROOT)
  set(HPX_INCLUDE_EXTERNAL_DIRS)
  foreach(ext cache endian atomic serialization asio)
    if(NOT IS_DIRECTORY ${Boost_INCLUDE_DIR}/boost/${ext} AND IS_DIRECTORY ${HPX_ROOT}/external/${ext})
      list(APPEND HPX_INCLUDE_EXTERNAL_DIRS ${HPX_ROOT}/external/${ext})
    endif()
  endforeach()
endif()

if(NOT HPX_INCLUDE_EXTERNAL_DIRS)
  find_file(HPX_INCLUDE_EXTERNAL_DIRS hpx/external)
endif()

if(NOT DEFINED HPX_LIBRARY_DIR)
  if(HPX_BINARY_ROOT)
    set(HPX_LIBRARY_DIR ${HPX_BINARY_ROOT}/lib)
  else()
    set(HPX_LIBRARY_DIR ${HPX_ROOT}/lib)
  endif()
endif()
find_library(HPX_LIBRARY hpx PATHS ${HPX_LIBRARY_DIR} PATH_SUFFIXES hpx)
find_library(HPX_LIBRARY_INIT hpx_init PATHS ${HPX_LIBRARY_DIR} PATH_SUFFIXES hpx)
find_library(HPX_LIBRARY_SERIALIZATION hpx_serialization PATHS ${HPX_LIBRARY_DIR} PATH_SUFFIXES hpx)

if(NOT Boost_FOUND OR NOT HPX_INCLUDE_DIR OR NOT HPX_INCLUDE_BINARY_DIR OR NOT HPX_LIBRARY)
  set(NT2_ARCH.HPX_DEPENDENCIES_FOUND 0)
endif()

set(NT2_ARCH.HPX_COMPILE_FLAGS "-DNT2_USE_HPX")
if(CMAKE_COMPILER_IS_GNUCXX)
  set(NT2_ARCH.HPX_COMPILE_FLAGS "${NT2_ARCH.HPX_COMPILE_FLAGS} -std=c++0x -include hpx/config.hpp")
elseif(MSVC)
  set(NT2_ARCH.HPX_COMPILE_FLAGS "${NT2_ARCH.HPX_COMPILE_FLAGS} /FIhpx/config.hpp")
endif

set(NT2_ARCH.HPX_DEPENDENCIES_INCLUDE_DIR ${HPX_INCLUDE_DIR} ${HPX_INCLUDE_EXTERNAL_DIRS})
if(HPX_BINARY_ROOT)
  list(APPEND NT2_ARCH.HPX_DEPENDENCIES_INCLUDE_DIR ${HPX_INCLUDE_BINARY_DIR})
endif()

set( NT2_ARCH.HPX_DEPENDENCIES_LIBRARIES ${HPX_LIBRARY} ${HPX_LIBRARY_INIT} ${HPX_LIBRARY_SERIALIZATION}
                                         ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_THREAD_LIBRARY}
                                         ${Boost_SYSTEM_LIBRARY} ${Boost_SERIALIZATION_LIBRARY}
   )

set( NT2_ARCH.HPX_DEPENDENCIES_EXTRA
     arch.shared_memory
     boost.dispatch
     sdk.functor
   )
