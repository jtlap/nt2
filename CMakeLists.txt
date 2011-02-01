################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
cmake_minimum_required(VERSION 2.6)

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
    )

# Generate the shared library.

add_library(nt2 SHARED ${source_files})
set_target_properties(nt2 PROPERTIES VERSION 3.0.0 SOVERSION 3)

# Cannot have two targets with the same name so the static version has
# '-static' appended and then the name of the output file is set
# separately.

add_library(nt2-static STATIC ${source_files})
set_target_properties(nt2-static PROPERTIES OUTPUT_NAME "nt2")

# These next two lines are required but it is unclear exactly what they do.
# The CMake FAQ mentions they are necessary and it does not work otherwise.
SET_TARGET_PROPERTIES(nt2 PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(nt2-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

################################################################################
# Install libnt2
################################################################################
INSTALL( DIRECTORY ${PROJECT_SOURCE_DIR}/include/
         DESTINATION ${CMAKE_INSTALL_PREFIX}/include
         FILES_MATCHING
         PATTERN "*.hpp"
       )

INSTALL( DIRECTORY ${PROJECT_BINARY_DIR}/include/
         DESTINATION ${CMAKE_INSTALL_PREFIX}/include
         FILES_MATCHING
         PATTERN "*.hpp"
       )

INSTALL( TARGETS nt2
	      LIBRARY DESTINATION lib/
	      ARCHIVE DESTINATION lib/)

INSTALL( TARGETS nt2-static
	      LIBRARY DESTINATION lib/
	      ARCHIVE DESTINATION lib/)

################################################################################
# Add Documentation target
################################################################################
ADD_CUSTOM_TARGET ( doc
                    COMMAND make html
                    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/doc
                  )

################################################################################
# Add Examples
################################################################################
ADD_CUSTOM_TARGET(examples
                  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/examples
                 )

ADD_SUBDIRECTORY(examples EXCLUDE_FROM_ALL)

################################################################################
# Add Unit Tests
################################################################################
ENABLE_TESTING()
ADD_CUSTOM_TARGET(unit)
ADD_SUBDIRECTORY(unit EXCLUDE_FROM_ALL)

################################################################################
# Add RT Benchmarks and the driver rule
################################################################################
ADD_CUSTOM_TARGET(benchmarks
                  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/benchmark
                 )

ADD_SUBDIRECTORY(benchmark EXCLUDE_FROM_ALL)

################################################################################
# System-level toolbox inclusion
################################################################################

ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/arithmetic EXCLUDE_FROM_ALL)
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/bitwise EXCLUDE_FROM_ALL)
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/trigonometric EXCLUDE_FROM_ALL)
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/predicates EXCLUDE_FROM_ALL)
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/ieee EXCLUDE_FROM_ALL)
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/fuzzy EXCLUDE_FROM_ALL)
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/hyperbolic EXCLUDE_FROM_ALL)
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/exponential EXCLUDE_FROM_ALL)
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/reduction EXCLUDE_FROM_ALL)
#ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/swar EXCLUDE_FROM_ALL)
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/elliptic EXCLUDE_FROM_ALL)
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/bessel EXCLUDE_FROM_ALL)
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/combinatorial EXCLUDE_FROM_ALL)
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/euler EXCLUDE_FROM_ALL)
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/polynomials EXCLUDE_FROM_ALL)

#ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/cephes EXCLUDE_FROM_ALL)
#ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/crlibm EXCLUDE_FROM_ALL)
#ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/ast EXCLUDE_FROM_ALL)
#ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/fdlibm EXCLUDE_FROM_ALL)
#ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/libc EXCLUDE_FROM_ALL)
#ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/standard EXCLUDE_FROM_ALL)
#ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/boost_math EXCLUDE_FROM_ALL)
#ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/include/nt2/toolbox/gsl_specfun EXCLUDE_FROM_ALL)

#ADD_SUBDIRECTORY(sandbox EXCLUDE_FROM_ALL)

################################################################################
# Post-config message
################################################################################
INCLUDE(nt2.directive)

