################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
set(NT2_SDK_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
include(nt2.sdk.dependencies)
set(NT2_CURRENT_MODULE sdk)

include_directories( ${PROJECT_BINARY_DIR}/include
                     ${CMAKE_CURRENT_SOURCE_DIR}/include
                     ${NT2_SDK_DEPENDENCIES_INCLUDE_DIR}
                   )

add_subdirectory(bench)

find_package(NT2 COMPONENTS predicates)
if(NT2_FOUND)
  include_directories( ${NT2_PREDICATES_INCLUDE_DIR} )
  add_subdirectory(examples)
endif()

add_subdirectory(unit)

if(NOT ${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
  nt2_flag_found()
endif()
