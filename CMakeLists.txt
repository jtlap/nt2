################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

################################################################################
# Project nt2 - See toolbox/CMakeLists.txt for toolbox CMake scripts
################################################################################
PROJECT(nt2)

################################################################################
# Global Options
################################################################################
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

SET(INCLUDE_INSTALL_DIR
    "${CMAKE_INSTALL_PREFIX}/include/nt2"
    CACHE PATH
    "The directory where we install the header files"
    FORCE)

SET(NT2_VERSION_NUMBER "3.0.0")
SET(NT2_VERSION "${NT2_VERSION_NUMBER}")

################################################################################
# Display some info
################################################################################
INCLUDE(nt2.info)

################################################################################
# Gather CXX flags from user options and configuration
################################################################################
INCLUDE(nt2.compiler.options)

################################################################################
# Build up NT2 related settings
################################################################################
INCLUDE(nt2.boost)
INCLUDE(nt2.sphinx)
INCLUDE(nt2.python)

################################################################################
# Find parallelism sources
################################################################################
INCLUDE(nt2.mpi)
INCLUDE(nt2.simd)
INCLUDE(nt2.threading)

################################################################################
# Find number CPU information

################################################################################
INCLUDE(nt2.cpucount)
INCLUDE(nt2.cpucache)

################################################################################
# Generate bootstrap.hpp
################################################################################
CONFIGURE_FILE( ${PROJECT_SOURCE_DIR}/cmake/bootstrap.hpp.cmake
                ${PROJECT_BINARY_DIR}/include/nt2/sdk/config/bootstrap.hpp
              )

################################################################################
# Build libnt2
################################################################################

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})

INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES( ${PROJECT_BINARY_DIR}/include)

FILE( GLOB_RECURSE source_files
      ${PROJECT_SOURCE_DIR}/src/*
    )

ADD_LIBRARY(nt2 STATIC ${source_files} )

################################################################################
# Install libnt2
################################################################################
INSTALL( DIRECTORY ${PROJECT_SOURCE_DIR}/include
         DESTINATION ${CMAKE_INSTALL_PREFIX} )
INSTALL( DIRECTORY ${PROJECT_BINARY_DIR}/include
         DESTINATION ${CMAKE_INSTALL_PREFIX} )

INSTALL( TARGETS nt2
	      LIBRARY DESTINATION lib/
	      ARCHIVE DESTINATION lib/)

################################################################################
# Add Documentation target
################################################################################
ADD_CUSTOM_TARGET ( doc
                    COMMAND make html
                    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/doc
                  )

################################################################################
# Add Examples
################################################################################
ADD_CUSTOM_TARGET(examples
                  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/examples
                 )

ADD_SUBDIRECTORY(examples)

################################################################################
# Add Unit Tests
################################################################################
ENABLE_TESTING()
ADD_SUBDIRECTORY(unit)

################################################################################
# Add RT Benchmarks and the driver rule
################################################################################
ADD_CUSTOM_TARGET(benchmarks
                  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/benchmark
                 )

ADD_SUBDIRECTORY(benchmark)

################################################################################
# System-level toolbox inclusion
################################################################################

#ADD_SUBDIRECTORY(${PROJECT_BINARY_DIR}/include/nt2/toolbox/arithmetic)
#ADD_SUBDIRECTORY(${PROJECT_BINARY_DIR}/include/nt2/toolbox/bitwise)
#ADD_SUBDIRECTORY(${PROJECT_BINARY_DIR}/include/nt2/toolbox/trigonometric)
#ADD_SUBDIRECTORY(${PROJECT_BINARY_DIR}/include/nt2/toolbox/predicates)
#ADD_SUBDIRECTORY(${PROJECT_BINARY_DIR}/include/nt2/toolbox/ieee)
#ADD_SUBDIRECTORY(${PROJECT_BINARY_DIR}/include/nt2/toolbox/fuzzy)
#ADD_SUBDIRECTORY(${PROJECT_BINARY_DIR}/include/nt2/toolbox/hyperbolic)
#ADD_SUBDIRECTORY(${PROJECT_BINARY_DIR}/include/nt2/toolbox/exponential)
#ADD_SUBDIRECTORY(${PROJECT_BINARY_DIR}/include/nt2/toolbox/reduction)
#ADD_SUBDIRECTORY(${PROJECT_BINARY_DIR}/include/nt2/toolbox/elliptic)
#ADD_SUBDIRECTORY(${PROJECT_BINARY_DIR}/include/nt2/toolbox/bessel)
#ADD_SUBDIRECTORY(${PROJECT_BINARY_DIR}/include/nt2/toolbox/combinatorial)
#ADD_SUBDIRECTORY(${PROJECT_BINARY_DIR}/include/nt2/toolbox/euler)

################################################################################
# Post-installation Directives
################################################################################
INCLUDE(nt2.directive)