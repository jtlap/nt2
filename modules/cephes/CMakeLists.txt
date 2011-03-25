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
include(nt2.cephes.dependencies)
if(NOT NT2_CEPHES_DEPENDENCIES_FOUND)
  message(WARNING "[nt2.cephes] dependencies not met, skipping module")
  return()
endif()

include_directories( ${PROJECT_BINARY_DIR}/include
                     ${CMAKE_CURRENT_SOURCE_DIR}/include
                     ${NT2_CEPHES_DEPENDENCIES_INCLUDE_DIR}
                   )

ADD_SUBDIRECTORY(src)

ADD_SUBDIRECTORY(bench EXCLUDE_FROM_ALL)

find_package(NT2 COMPONENTS arithmetic euler
                            exponential trigonometric
                            bessel hyperbolic
                            elliptic
            )
if(NOT NT2_FOUND)
  message(WARNING "[nt2.cephes] dependencies for unit tests not met, skipping")
else()
  include_directories(${NT2_INCLUDE_DIR})
  link_directories(${NT2_LIBRARY_DIR})
  ADD_SUBDIRECTORY(unit EXCLUDE_FROM_ALL)
endif()

if(NOT ${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
  nt2_flag_found()
endif()
