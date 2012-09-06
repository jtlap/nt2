################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
cmake_minimum_required(VERSION 2.6)

set(NT2_SOURCE_ROOT ${CMAKE_SOURCE_DIR}/../..)
set(CMAKE_MODULE_PATH ${NT2_SOURCE_ROOT}/cmake)
find_package(NT2 REQUIRED COMPONENTS boost.simd.detect)
include_directories(${NT2_INCLUDE_DIR})
link_directories(${NT2_LIBRARY_DIR})
link_libraries(${NT2_LIBRARIES})

add_executable(is_multicore is_multicore.cpp)
set_target_properties(is_multicore
                      PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}
                                 RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}
                     )
