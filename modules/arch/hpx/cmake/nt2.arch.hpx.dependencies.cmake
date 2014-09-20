################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(nt2.info)
include(nt2.boost)
find_package(Boost 1.53.0 QUIET COMPONENTS program_options thread system serialization filesystem)

if(NOT DEFINED HPX_ROOT)
  set(HPX_ROOT $ENV{HPX_ROOT})
endif()
if(NOT DEFINED HPX_BINARY_ROOT)
  set(HPX_BINARY_ROOT $ENV{HPX_BINARY_ROOT})
endif()
find_path(HPX_INCLUDE_DIR hpx/hpx.hpp PATHS ${HPX_ROOT} PATH_SUFFIXES include NO_DEFAULT_PATH)
find_path(HPX_INCLUDE_DIR hpx/hpx.hpp)
find_path(HPX_INCLUDE_BINARY_DIR hpx/config/defines.hpp PATHS ${HPX_BINARY_ROOT} ${HPX_ROOT} PATH_SUFFIXES include NO_DEFAULT_PATH)
find_path(HPX_INCLUDE_BINARY_DIR hpx/config/defines.hpp)

if(HPX_ROOT)
  set(HPX_INCLUDE_EXTERNAL_DIRS)
  foreach(ext cache endian atomic serialization asio)
    if(NOT IS_DIRECTORY ${Boost_INCLUDE_DIR}/boost/${ext} AND IS_DIRECTORY ${HPX_ROOT}/external/${ext})
      list(APPEND HPX_INCLUDE_EXTERNAL_DIRS ${HPX_ROOT}/external/${ext})
    endif()
  endforeach()
endif()

if(NOT HPX_INCLUDE_EXTERNAL_DIRS)
  find_file(HPX_INCLUDE_EXTERNAL_DIRS hpx/external PATHS ${HPX_INCLUDE_DIR} NO_DEFAULT_PATH)
  find_file(HPX_INCLUDE_EXTERNAL_DIRS hpx/external)
endif()

if(NOT DEFINED HPX_LIBRARY_DIR)
  if(HPX_BINARY_ROOT)
    if(IS_DIRECTORY ${HPX_BINARY_ROOT}/lib)
      set(HPX_LIBRARY_DIR ${HPX_BINARY_ROOT}/lib)
    else()
      set(HPX_LIBRARY_DIR ${HPX_BINARY_ROOT}/Release/lib ${HPX_BINARY_ROOT}/Debug/lib)
    endif()
  else()
    set(HPX_LIBRARY_DIR ${HPX_ROOT}/lib)
  endif()
endif()

foreach(lib hpx hpx_init hpx_serialization)
  string(TOUPPER ${lib} lib_U)
  find_library(${lib_U}_LIBRARY_RELEASE ${lib} PATHS ${HPX_LIBRARY_DIR} PATH_SUFFIXES hpx NO_DEFAULT_PATH)
  find_library(${lib_U}_LIBRARY_RELEASE ${lib} PATH_SUFFIXES hpx)

  find_library(${lib_U}_LIBRARY_DEBUG ${lib}d PATHS ${HPX_LIBRARY_DIR} PATH_SUFFIXES hpx NO_DEFAULT_PATH)
  find_library(${lib_U}_LIBRARY_DEBUG ${lib}d PATH_SUFFIXES hpx)

  if(${lib_U}_LIBRARY_DEBUG AND ${lib_U}_LIBRARY_RELEASE)
    set(${lib_U}_LIBRARY debug ${${lib_U}_LIBRARY_DEBUG} optimized ${${lib_U}_LIBRARY_RELEASE})
  else()
    set(${lib_U}_LIBRARY ${${lib_U}_LIBRARY_RELEASE})
  endif()
endforeach()

if(NOT Boost_FOUND OR NOT HPX_INCLUDE_DIR OR NOT HPX_INCLUDE_BINARY_DIR OR NOT HPX_LIBRARY)
  set(NT2_ARCH.HPX_DEPENDENCIES_FOUND 0)
endif()

set(NT2_ARCH.HPX_COMPILE_FLAGS "-DNT2_USE_HPX -DNOMINMAX")

if(NOT Boost_USE_STATIC_LIBS)
 set(NT2_ARCH.HPX_COMPILE_FLAGS "${NT2_ARCH.HPX_COMPILE_FLAGS} -DBOOST_ALL_DYN_LINK")
endif()

if(NT2_COMPILER_GCC_LIKE)
  set(NT2_ARCH.HPX_COMPILE_FLAGS "${NT2_ARCH.HPX_COMPILE_FLAGS} -fexceptions -std=c++0x -include hpx/config.hpp")
elseif(MSVC)
  set(NT2_ARCH.HPX_COMPILE_FLAGS "${NT2_ARCH.HPX_COMPILE_FLAGS} /FIhpx/config.hpp /FIwinsock2.h")
endif()

set(NT2_ARCH.HPX_DEPENDENCIES_INCLUDE_DIR ${HPX_INCLUDE_DIR} ${HPX_INCLUDE_EXTERNAL_DIRS})
if(HPX_BINARY_ROOT)
  list(APPEND NT2_ARCH.HPX_DEPENDENCIES_INCLUDE_DIR ${HPX_INCLUDE_BINARY_DIR})
endif()

set( NT2_ARCH.HPX_DEPENDENCIES_LIBRARIES ${HPX_LIBRARY} ${HPX_INIT_LIBRARY} ${HPX_SERIALIZATION_LIBRARY} )

foreach(lib PROGRAM_OPTIONS THREAD SYSTEM SERIALIZATION FILESYSTEM)
  if(Boost_${lib}_LIBRARY_DEBUG AND Boost_${lib}_LIBRARY_RELEASE)
    list(APPEND NT2_ARCH.HPX_DEPENDENCIES_LIBRARIES debug ${Boost_${lib}_LIBRARY_DEBUG} optimized ${Boost_${lib}_LIBRARY_RELEASE})
  else()
    list(APPEND NT2_ARCH.HPX_DEPENDENCIES_LIBRARIES ${Boost_${lib}_LIBRARY_RELEASE})
  endif()
endforeach()

set( NT2_ARCH.HPX_DEPENDENCIES_EXTRA
     arch.shared_memory
     boost.dispatch
     sdk.functor
   )
