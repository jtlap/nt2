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
set(NT2_MODULES_BLACKLIST cuda matlab openmp)
find_package(NT2 REQUIRED)
include(${NT2_USE_FILE})
include(nt2.template.profiler)

set( SOURCES
     scalar_functor.cpp
   )

foreach(src ${SOURCES})
  string(REGEX REPLACE "\\.cpp$" "" exe ${src})
  string(REGEX REPLACE "\\.cpp$" ".run" run ${src})
  template_profile(${exe} ${src})
  add_executable(${run} ${src})
endforeach()
