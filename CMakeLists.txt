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
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include(nt2.compiler.options)

################################################################################
# Global Options
################################################################################
set(NT2_VERSION_NUMBER "3.0.0")
set(NT2_VERSION "${NT2_VERSION_NUMBER}")

################################################################################
# Add Documentation target
################################################################################
#ADD_CUSTOM_TARGET ( doc
#                    COMMAND make html
#                    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/doc
#                  )

################################################################################
# Add super-targets
################################################################################
ADD_CUSTOM_TARGET( bench
                   WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/bench
                 )
ADD_CUSTOM_TARGET( examples
                   WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/examples
                 )
ENABLE_TESTING()
ADD_CUSTOM_TARGET( unit
                   WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/unit
                 )

################################################################################
# Module inclusion
################################################################################

macro(nt2_load_module module)
  add_subdirectory(${PROJECT_SOURCE_DIR}/modules/${module})
  add_dependencies(bench ${module}.bench)
  add_dependencies(examples ${module}.examples)
  add_dependencies(unit ${module}.unit)
endmacro()

set(NT2_SOURCE_ROOT ${PROJECT_SOURCE_DIR})

file(GLOB MODULES RELATIVE ${PROJECT_SOURCE_DIR}/modules ${PROJECT_SOURCE_DIR}/modules/*/)
foreach(module ${MODULES})
  if(EXISTS ${PROJECT_SOURCE_DIR}/modules/${module}/CMakeLists.txt)
    message(STATUS "[nt2] loading module ${module}")
    nt2_load_module(${module})
  endif()
endforeach()

ADD_SUBDIRECTORY(sandbox)

################################################################################
# Post-config message
################################################################################
INCLUDE(nt2.directive) 
