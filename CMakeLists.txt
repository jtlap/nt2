################################################################################
##         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
##         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
##
##          Distributed under the Boost Software License, Version 1.0.
##                 See accompanying file LICENSE.txt or copy at
##                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
cmake_minimum_required(VERSION 2.6)

################################################################################
# Project nt2 that loads many modules
# -- see modules/(<module>/+)CMakeLists.txt to build a single module.
################################################################################
project(NT2)

################################################################################
# If GIT repo, verify pre-commit hooks are well set-up
################################################################################
if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/.git/hooks)
  execute_process(COMMAND ${CMAKE_COMMAND} -E copy
                  ${PROJECT_SOURCE_DIR}/script/git/pre-commit
                  ${PROJECT_SOURCE_DIR}/.git/hooks
                 )
endif()

################################################################################
# Set-up NT2 CMake environment
################################################################################
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
include(nt2.compiler.options)

set(NT2_VERSION "3.0.0")
include(nt2.package)

################################################################################
# Start configuration
################################################################################
set(NT2_SOURCE_ROOT ${PROJECT_SOURCE_DIR})
include(NT2Module)
nt2_configure_tests()
nt2_postconfigure_init()

################################################################################
# Module inclusion
################################################################################
set(NT2_MODULES_EXTRA "" CACHE STRING "Extra modules to load")
set(NT2_MODULES_BLACKLIST "" CACHE STRING "Modules that should not be loaded")

################################################################################
# We load all directories of modules/ for which a CMakeLists.txt is present;
# if none is found in the directory, we search recursively until we find one.
################################################################################
if(NOT NT2_MODULES)
  file(GLOB NT2_MODULES RELATIVE ${PROJECT_SOURCE_DIR}/modules ${PROJECT_SOURCE_DIR}/modules/*/)
  set(i 0)
  list(LENGTH NT2_MODULES len)
  while(i LESS len)
    list(GET NT2_MODULES ${i} module)
    string(REPLACE "." "/" module_path ${module})
    if(${module} MATCHES boostification)
      list(REMOVE_ITEM NT2_MODULES ${module})
      list(LENGTH NT2_MODULES len)
    elseif(NOT EXISTS ${PROJECT_SOURCE_DIR}/modules/${module_path}/CMakeLists.txt)
      list(REMOVE_ITEM NT2_MODULES ${module})
      file(GLOB NT2_MODULES_ RELATIVE ${PROJECT_SOURCE_DIR}/modules ${PROJECT_SOURCE_DIR}/modules/${module_path}/*/)
      if(NT2_MODULES_)
        string(REPLACE "/" "." NT2_MODULES_ "${NT2_MODULES_}")
        list(APPEND NT2_MODULES ${NT2_MODULES_})
      endif()
      list(LENGTH NT2_MODULES len)
    else()
      math(EXPR i "${i} + 1")
    endif()
  endwhile()
endif()

if(NT2_MODULES_EXTRA)
  list(APPEND NT2_MODULES ${NT2_MODULES_EXTRA})
  list(REMOVE_DUPLICATES "NT2_MODULES")
endif()

################################################################################
# Download extra modules and set include directories
################################################################################
include(nt2.download)
foreach(module ${NT2_MODULES})
  list(FIND NT2_MODULES_BLACKLIST ${module} module_found)
  if(module_found LESS 0)
    string(REPLACE "." "/" module_path ${module})

    if(NOT IS_DIRECTORY ${PROJECT_SOURCE_DIR}/modules/${module_path})
      nt2_download_module(${module})
    endif()

    include_directories(${PROJECT_SOURCE_DIR}/modules/${module_path}/include)

  endif()
endforeach()

################################################################################
# Load modules
################################################################################
foreach(module ${NT2_MODULES})
  list(FIND NT2_MODULES_BLACKLIST ${module} module_found)
  if(module_found LESS 0)
    string(REPLACE "." "/" module_path ${module})

    if(NOT IS_DIRECTORY ${PROJECT_SOURCE_DIR}/modules/${module_path})
      message(STATUS "[nt2] module ${module} not found")
    else()
      message(STATUS "[nt2] loading module ${module}")
      add_subdirectory(modules/${module_path})
    endif()

  endif()
endforeach()

################################################################################
# Setup documentation after all modules have been downloaded
################################################################################
if(NT2_DOCUMENTATION_ENABLED)
  add_subdirectory(doc)
endif()

################################################################################
# Ensure all tools get set up
################################################################################
file(GLOB NT2_TOOLS RELATIVE ${PROJECT_SOURCE_DIR}/tools ${PROJECT_SOURCE_DIR}/tools/*/)
foreach(tool ${NT2_TOOLS})
  nt2_module_tool_setup(${tool})
endforeach()

set(CMAKE_MODULE_PATH ${NT2_MODULE_PATH})

################################################################################
# Post-config phase
################################################################################
nt2_postconfigure_run()
include(nt2.directive)
