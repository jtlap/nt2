################################################################################
##         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
##         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
##
##          Distributed under the Boost Software License, Version 1.0.
##                 See accompanying file LICENSE.txt or copy at
##                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
cmake_minimum_required(VERSION 2.8)

################################################################################
# Project nt2 that loads many modules
# -- see modules/(<module>/+)CMakeLists.txt to build a single module.
################################################################################
if(NOT CMAKE_GENERATOR MATCHES "Make|Ninja")
  set(CMAKE_CONFIGURATION_TYPES Release Debug NT2Test NT2TestDebug NT2Bench CACHE STRING "" FORCE)
endif()
project(NT2)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

find_package(Git QUIET)
if(GIT_EXECUTABLE)
  execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                  OUTPUT_VARIABLE NT2_VERSION_STRING
                  OUTPUT_STRIP_TRAILING_WHITESPACE
                 )
endif()
if(NOT NT2_VERSION_STRING)
  if(NOT EXISTS ${PROJECT_SOURCE_DIR}/tagname)
    message(FATAL_ERROR "NT2_VERSION_STRING must be specified manually if no tagname file nor Git")
  endif()
  file(READ tagname NT2_VERSION_STRING)
  string(REGEX REPLACE "[ \r\n\t]+$" "" NT2_VERSION_STRING "${NT2_VERSION_STRING}")
endif()

include(nt2.parse_version)
nt2_parse_version("${NT2_VERSION_STRING}" NT2_VERSION)

set(nt2_release "(release)")
if(NT2_VERSION_IS_PRERELEASE)
  set(nt2_release "(pre-release)")
endif()

message(STATUS "[nt2] Configuring NT2 version ${NT2_VERSION_STRING} ${nt2_release}")

################################################################################
# Install pre-commit git hook
################################################################################
execute_process(COMMAND ${CMAKE_COMMAND} -E copy
                ${PROJECT_SOURCE_DIR}/script/git/pre-commit
                ${PROJECT_SOURCE_DIR}/.git/hooks
               )

################################################################################
# Set-up NT2 CMake environment
################################################################################
include(nt2.compiler.options)
include(nt2.package)

################################################################################
# Start configuration
################################################################################
set(NT2_SOURCE_ROOT ${PROJECT_SOURCE_DIR})
include(NT2Module)

# We need Boost for pretty much everything, we might as well search for it now
include(nt2.boost)
if(NOT Boost_FOUND)
  message(FATAL_ERROR "NT2 requires a recent version of Boost but none recent enough was found")
endif()

nt2_module_configure_file(version.hpp.in nt2/version.hpp)

nt2_configure_tests()
nt2_postconfigure_init()

################################################################################
# Module inclusion
################################################################################
set(NT2_MODULES_EXTRA "" CACHE STRING "Extra modules to load")
set(NT2_MODULES_BLACKLIST "" CACHE STRING "Modules that should not be loaded")

################################################################################
# If no explicit modules are set, we use all modules we can find
################################################################################
if(NOT NT2_MODULES)
  file(GLOB NT2_MODULES RELATIVE ${PROJECT_SOURCE_DIR}/modules ${PROJECT_SOURCE_DIR}/modules/*/)
endif()
nt2_expand_submodules(NT2_MODULES)
nt2_remove_blacklisted(NT2_MODULES)

################################################################################
# Download extra modules
################################################################################
include(nt2.download)
list(REMOVE_DUPLICATES NT2_MODULES_EXTRA)
nt2_remove_blacklisted(NT2_MODULES_EXTRA)
foreach(module ${NT2_MODULES_EXTRA})
    string(REPLACE "." "/" module_path ${module})

    if(NOT IS_DIRECTORY ${PROJECT_SOURCE_DIR}/modules/${module_path})
      nt2_download_module(${module})
    endif()
endforeach()
nt2_expand_submodules(NT2_MODULES_EXTRA)
nt2_remove_blacklisted(NT2_MODULES_EXTRA)
if(NT2_MODULES_EXTRA)
  list(APPEND NT2_MODULES ${NT2_MODULES_EXTRA})
  list(REMOVE_DUPLICATES NT2_MODULES)
endif()

################################################################################
# Set include directories
################################################################################
foreach(module ${NT2_MODULES})
  string(REPLACE "." "/" module_path ${module})
  include_directories(${PROJECT_SOURCE_DIR}/modules/${module_path}/include)
endforeach()

################################################################################
# Global modules
################################################################################
if(DEFINED NT2_MODULES_GLOBAL)
  message(STATUS "[nt2] Selected global modules: ${NT2_MODULES_GLOBAL}")
  set(NT2_CURRENT_MODULE main)
  nt2_expand_submodules(NT2_MODULES_GLOBAL)
  nt2_module_use_modules(${NT2_MODULES_GLOBAL})
  set(NT2_CURRENT_MODULE)
endif()

################################################################################
# Load modules
################################################################################
set(stage_inputs)
foreach(module ${NT2_MODULES})
  string(REPLACE "." "/" module_path ${module})
  if(NOT IS_DIRECTORY ${PROJECT_SOURCE_DIR}/modules/${module_path})
    message(STATUS "[nt2] module ${module} not found")
  else()
    message(STATUS "[nt2] loading module ${module}")
    add_subdirectory(modules/${module_path})
    list(APPEND stage_inputs ${CMAKE_SOURCE_DIR}/modules/${module_path}/include)
  endif()
endforeach()

################################################################################
# Merge include directories in stage target
################################################################################
add_custom_target(stage
                  COMMAND ${CMAKE_COMMAND}
                          "-DOUTPUT=${CMAKE_BINARY_DIR}/include"
                          "-DINPUTS=\"${stage_inputs}\""
                          -P ${CMAKE_SOURCE_DIR}/cmake/nt2.merge_directories.cmake
                  COMMENT "Merging includes..."
                 )

################################################################################
# Setup documentation after all modules have been downloaded
################################################################################
add_subdirectory(doc)

################################################################################
# Ensure all tools get set up
################################################################################
file(GLOB NT2_TOOLS RELATIVE ${PROJECT_SOURCE_DIR}/tools ${PROJECT_SOURCE_DIR}/tools/*/)
foreach(tool ${NT2_TOOLS})
  if(NOT ${tool} MATCHES "^\\.")
    nt2_module_tool_setup(${tool})
  endif()
endforeach()

################################################################################
# Post-config phase
################################################################################
nt2_postconfigure_run()
include(nt2.directive)

################################################################################
# external projects: demo and sandbox
################################################################################
include(ExternalProject)

# we want to build those external projects with the same configuration
set(CMAKE_OPTIONS)
foreach(var NT2_SIMD_FLAGS NT2_MODULES_BLACKLIST
            CMAKE_C_COMPILER CMAKE_CXX_COMPILER
            CMAKE_C_FLAGS CMAKE_CXX_FLAGS CMAKE_TOOLCHAIN_FILE
            CMAKE_FIND_ROOT_PATH CMAKE_FIND_ROOT_PATH_MODE_PROGRAM
            CMAKE_FIND_ROOT_PATH_MODE_LIBRARY CMAKE_FIND_ROOT_PATH_MODE_INCLUDE
       )
  if(DEFINED ${var})
    list(APPEND CMAKE_OPTIONS "-D${var}:STRING=${${var}}")
  endif()
endforeach()
foreach(var CMAKE_SYSTEM_NAME CMAKE_SYSTEM_VERSION CMAKE_SYSTEM_PROCESSOR)
  if(DEFINED ${var} AND CMAKE_CROSSCOMPILING)
    list(APPEND CMAKE_OPTIONS "-D${var}:STRING=${${var}}")
  endif()
endforeach()

set(BUILD)
if(CMAKE_GENERATOR STREQUAL Ninja)
  set(BUILD BUILD_COMMAND ninja -j2)
endif()

foreach(project demo sandbox)
  ExternalProject_Add( ${project} SOURCE_DIR ${CMAKE_SOURCE_DIR}/${project} BINARY_DIR ${CMAKE_BINARY_DIR}/${project}
                       CMAKE_CACHE_ARGS ${CMAKE_OPTIONS} ${BUILD} INSTALL_COMMAND ""
                       STEP_TARGETS configure
                     )
  set_target_properties(${project} PROPERTIES EXCLUDE_FROM_ALL TRUE)
  set_target_properties(${project}-configure PROPERTIES EXCLUDE_FROM_ALL FALSE)
endforeach()
