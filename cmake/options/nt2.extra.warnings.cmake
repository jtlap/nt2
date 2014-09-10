################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Setup some compliler options
################################################################################
include(CheckCXXCompilerFlag)
include(nt2.info)

################################################################################
# Add Extra warning level
################################################################################
if(NT2_COMPILER_GCC_LIKE)
  option(NT2_EXTRA_WARNINGS "Enable/disable extra warnings" ON)
else()
  option(NT2_EXTRA_WARNINGS "Enable/disable extra warnings" OFF)
endif()

if(NT2_EXTRA_WARNINGS)
  message(STATUS "[nt2] extra warnings enabled")
endif()

if(NT2_COMPILER_GCC_LIKE)
  set(HAS_GCC_WALL 1)
  set(HAS_GCC_WEXTRA 1)
  set(HAS_GCC_WSHADOW 1)
  set(HAS_MSVC_W4 0)
elseif(MSVC)
  set(HAS_GCC_WALL 0)
  set(HAS_GCC_WEXTRA 0)
  set(HAS_GCC_WSHADOW 0)
  set(HAS_MSVC_W4 1)
endif()

################################################################################
# Check for GCC style
################################################################################
if(NT2_EXTRA_WARNINGS)
  if(NOT DEFINED HAS_GCC_WEXTRA)
    check_cxx_compiler_flag("-Wextra" HAS_GCC_WEXTRA)
  endif()
  if(HAS_GCC_WEXTRA)
    set(HAS_GCC_WALL 1)
  endif()
  if(NOT DEFINED HAS_GCC_WSHADOW)
    check_cxx_compiler_flag("-Wshadow" HAS_GCC_WSHADOW)
  endif()
endif()

  if(NOT DEFINED HAS_GCC_WALL)
    check_cxx_compiler_flag("-Wall" HAS_GCC_WALL)
  endif()

  if(HAS_GCC_WALL)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    check_cxx_compiler_flag("-Wno-delete-non-virtual-dtor" HAS_GCC_NO_DELETE_NON_VIRTUAL_DTOR)
    if(HAS_GCC_NO_DELETE_NON_VIRTUAL_DTOR)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-delete-non-virtual-dtor")
    endif()
    # array bounds warnings give many false positives in GCC >= 4.4
    if(CMAKE_COMPILER_IS_GNUCXX AND "${CMAKE_CXX_COMPILER_VERSION}" MATCHES "^4\\.[4-9]")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-array-bounds")
    endif()
  endif()
if(NT2_EXTRA_WARNINGS)
  if(HAS_GCC_WEXTRA)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
  endif()
  if(HAS_GCC_WSHADOW)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wshadow")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow")
  endif()
elseif(HAS_GCC_WALL)
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused")
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused")
endif()

################################################################################
# Check for MSVC style
################################################################################
if(NT2_EXTRA_WARNINGS)
  if(NOT DEFINED HAS_MSVC_W4)
    check_cxx_compiler_flag("/W4" HAS_MSVC_W4)
  endif()

  if(HAS_MSVC_W4)

    if("${CMAKE_C_FLAGS}" MATCHES "/W[1-4]")
      string(REGEX REPLACE "/W[1-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    else()
      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
    endif()
    if("${CMAKE_CXX_FLAGS}" MATCHES "/W[1-4]")
      string(REGEX REPLACE "/W[1-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
  endif()
endif()
