################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
cmake_minimum_required(VERSION 2.8)

################################################################################
# Project nt2 - See toolbox/CMakeLists.txt for toolbox CMake scripts
################################################################################
project(nt2)

################################################################################
# Global Options
################################################################################
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(INCLUDE_INSTALL_DIR
    "${CMAKE_INSTALL_PREFIX}/include/nt2"
    CACHE PATH
    "The directory where we install the header files"
    FORCE)

set(NT2_VERSION_NUMBER "3.0.0")
set(NT2_VERSION "${NT2_VERSION_NUMBER}")

################################################################################
# Display some info
################################################################################
include(nt2.info)

################################################################################
# Gather CXX flags from user options and configuration
################################################################################
include(nt2.compiler.options)

################################################################################
# Build up NT2 related settings
################################################################################
include(nt2.boost)
include(nt2.sphinx)
include(nt2.python)

################################################################################
# Find parallelism sources
################################################################################
include(nt2.mpi)
include(nt2.simd)
include(nt2.threading)

################################################################################
# Find number CPU information
################################################################################
include(nt2.cpucount)
include(nt2.cpucache)

################################################################################
# Generate bootstrap.hpp
################################################################################
CONFIGURE_FILE( ${PROJECT_SOURCE_DIR}/cmake/bootstrap.hpp.cmake
                ${PROJECT_BINARY_DIR}/include/nt2/sdk/config/bootstrap.hpp
              )

################################################################################
# Build libnt2
################################################################################

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})

include_directories( ${PROJECT_SOURCE_DIR}/include)
include_directories( ${PROJECT_BINARY_DIR}/include)

file( GLOB_RECURSE source_files
      ${PROJECT_SOURCE_DIR}/src/*
      ${PROJECT_SOURCE_DIR}/include/*
		  ${PROJECT_BINARY_DIR}/include/*
    )

add_library(nt2 STATIC ${source_files} )

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
ADD_SUBDIRECTORY(examples)

################################################################################
# Add Unit Tests
################################################################################
ENABLE_TESTING()
ADD_SUBDIRECTORY(unit)

################################################################################
# Add RT Benchmarks
################################################################################
ADD_SUBDIRECTORY(benchmark)


