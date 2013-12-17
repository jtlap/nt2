################################################################################
#         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
#         Copyright 2012 - 2013 MetaScale SAS
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
cmake_minimum_required(VERSION 2.8)

set(NT2_DIR ${CMAKE_SOURCE_DIR}/../cmake)

find_package(NT2 REQUIRED)
include(${NT2_USE_FILE})

set(CMAKE_BUILD_TYPE Release)
if(CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(-DBOOST_SIMD_NO_STRICT_ALIASING -fno-strict-aliasing)
endif()

#helloworld
add_subdirectory(helloworld/nt2)
add_subdirectory(helloworld/simd)

#blackscholes
add_subdirectory(blackscholes/scalar)
add_subdirectory(blackscholes/nt2)
add_subdirectory(blackscholes/simd)

#mandelbrot
add_subdirectory(mandelbrot/scalar)
add_subdirectory(mandelbrot/simd)

#rgb2yuv
add_subdirectory(rgb2yuv/scalar)
add_subdirectory(rgb2yuv/nt2)
add_subdirectory(rgb2yuv/simd)

#saxpy
add_subdirectory(saxpy/scalar)
add_subdirectory(saxpy/simd)

#sigmadelta
add_subdirectory(sigmadelta/scalar)
add_subdirectory(sigmadelta/simd)

#sdot
add_subdirectory(sdot/scalar)
add_subdirectory(sdot/simd)

