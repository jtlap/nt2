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
include(dependencies.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include NT2_SDK_DEPENDENCIES_INCLUDE_DIR)

################################################################################
# Generate bootstrap.hpp
################################################################################
CONFIGURE_FILE( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/bootstrap.hpp.cmake
                ${PROJECT_BINARY_DIR}/include/nt2/sdk/config/bootstrap.hpp
              )

add_subdirectory(bench)
add_subdirectory(examples)
add_subdirectory(unit)
