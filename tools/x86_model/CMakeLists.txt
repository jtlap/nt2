################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
cmake_minimum_required(VERSION 2.6)

set(NT2_DIR ${CMAKE_SOURCE_DIR}/../../cmake)
find_package(NT2 REQUIRED COMPONENTS boost.simd.detect)
include(${NT2_USE_FILE})

include(nt2.info)
if(NOT NT2_ARCH_X86)
  return()
endif()

add_executable(x86_model x86_model.cpp)
set_target_properties(x86_model
                      PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}
                                 RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}
                     )
