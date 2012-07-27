################################################################################
#         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
cmake_minimum_required(VERSION 2.8)

set(NT2_DIR ${CMAKE_SOURCE_DIR}/../../cmake)
set(NT2_MODULES_BLACKLIST cuda matlab cephes)
find_package(NT2 REQUIRED)
include(${NT2_USE_FILE})

set(CMAKE_BUILD_TYPE Release)
add_definitions(-fno-strict-aliasing -DBOOST_SIMD_NO_STRICT_ALIASING -DBOOST_DISABLE_ASSERTS)

add_executable(blackscholes blackscholes.cpp)
