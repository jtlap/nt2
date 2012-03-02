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

################################################################################
# Add Extra warning level
################################################################################
option(NT2_EXTRA_WARNINGS "Enable/disable extra warnings" OFF)

if(NT2_EXTRA_WARNINGS)
  message(STATUS "[nt2] extra warnings enabled")
endif()

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(HAS_GCC_WALL 1)
  set(HAS_MSVC_W4 0)
elseif(MSVC)
  set(HAS_GCC_WALL 0)
  set(HAS_GCC_WEXTRA 0)
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
endif()
  
  if(NOT DEFINED HAS_GCC_WALL)
    check_cxx_compiler_flag("-Wall" HAS_GCC_WALL)
  endif()
    
  if(HAS_GCC_WALL)
    set(NT2_FLAGS "${NT2_FLAGS} -Wall")
  endif()
if(NT2_EXTRA_WARNINGS)
  if(HAS_GCC_WEXTRA)
    set(NT2_FLAGS "${NT2_FLAGS} -Wextra")
  endif()
endif()

################################################################################
# Check for MSVC style
################################################################################
if(NT2_EXTRA_WARNINGS)
  if(NOT DEFINED HAS_MSVC_W4)
    check_cxx_compiler_flag("/W4" HAS_MSVC_W4)
  endif()
  
  if(HAS_MSVC_W4)
    set(NT2_FLAGS "${NT2_FLAGS} /W4")
  endif()
endif()
