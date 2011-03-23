################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(nt2.compiler.options)
include(nt2.boost)
include(nt2.simd)

################################################################################
# Generate bootstrap.hpp
################################################################################
FIND_FILE(NT2_SDK_BOOTSTRAP_FILE bootstrap.hpp.cmake ${CMAKE_MODULE_PATH})
CONFIGURE_FILE( ${NT2_SDK_BOOTSTRAP_FILE}
                ${PROJECT_BINARY_DIR}/include/nt2/sdk/config/bootstrap.hpp
              )

FIND_PACKAGE(NT2 COMPONENTS extension)
SET(NT2_SDK_DEPENDENCIES_FOUND ${NT2_FOUND})
SET(NT2_SDK_DEPENDENCIES_INCLUDE_DIR ${NT2_INCLUDE_DIR})

file( GLOB_RECURSE source_files
      ${NT2_SDK_ROOT}/src/*
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
SET(NT2_SDK_LIBRARIES nt2)
