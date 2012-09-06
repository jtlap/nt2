################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
cmake_minimum_required(VERSION 2.6)

set(NT2_DIR ${CMAKE_SOURCE_DIR}/../cmake)
set(NT2_MODULES_BLACKLIST cuda)
find_package(NT2 REQUIRED)
include(${NT2_USE_FILE})

add_definitions(-DBOOST_SIMD_NO_STRICT_ALIASING -fno-strict-aliasing)

set( SOURCES
#    rec_block.cpp
     pack.cpp
#    foo.cpp
#    table_dim.cpp
     transform_pass.cpp
     table.cpp
     index_test.cpp
   )

foreach(src ${SOURCES})
  string(REGEX REPLACE "\\.cpp$" "" exe ${src})
  add_executable(${exe} ${src})
endforeach()
