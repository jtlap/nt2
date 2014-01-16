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

# from global modules, only *.config modules are added
set(NT2_MODULES_GLOBAL_CONFIG)
foreach(module ${NT2_MODULES_GLOBAL})
  if("${module}" MATCHES "\\.config$")
    list(APPEND NT2_MODULES_GLOBAL_CONFIG ${module})
  endif()
endforeach()

find_package(NT2 REQUIRED COMPONENTS boost.simd.config ${NT2_MODULES_GLOBAL_CONFIG})
include(${NT2_USE_FILE})

add_executable(is_supported is_supported.cpp)
set_target_properties(is_supported
                      PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}
                                 RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}
                     )
