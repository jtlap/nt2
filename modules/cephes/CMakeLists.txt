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

include_directories( ${PROJECT_BINARY_DIR}/include
                     ${CMAKE_CURRENT_SOURCE_DIR}/include
                     ${NT2_CEPHES_DEPENDENCIES_INCLUDE_DIR}
                   )

ADD_SUBDIRECTORY(src/cephes_single)
ADD_SUBDIRECTORY(src/cephes_double)
IF(NOT WIN32)
  ADD_SUBDIRECTORY(src/cephes_ldouble)
ENDIF()

ADD_SUBDIRECTORY(bench)

find_package(NT2 COMPONENTS arithmetic euler
                            exponential trigonometric
                            bessel hyperbolic
                            elliptic
            )
include_directories( ${NT2_ARITHMETIC_INCLUDE_DIR} ${NT2_EULER_INCLUDE_DIR}
                     ${NT2_EXPONENTIAL_INCLUDE_DIR} ${NT2_TRIGONOMETRIC_INCLUDE_DIR}
                     ${NT2_BESSEL_INCLUDE_DIR} ${NT2_HYPERBOLIC_INCLUDE_DIR}
                     ${NT2_ELLIPTIC_INCLUDE_DIR}
                   )
ADD_SUBDIRECTORY(unit)
