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
include(nt2.sdk.dependencies)

include_directories( ${PROJECT_BINARY_DIR}/include
                     ${CMAKE_CURRENT_SOURCE_DIR}/include
                     ${NT2_SDK_DEPENDENCIES_INCLUDE_DIR}
                   )

file( GLOB_RECURSE source_files
      ${CMAKE_CURRENT_SOURCE_DIR}/src/*
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

add_subdirectory(bench)

find_package(NT2 COMPONENTS predicates)
include_directories( ${NT2_PREDICATES_INCLUDE_DIR} )
add_subdirectory(examples)

add_subdirectory(unit)
