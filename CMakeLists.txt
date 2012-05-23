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

# We need Boost for pretty much everything, we might as well search for it now
include(nt2.boost)
if(NOT Boost_FOUND)
  message(FATAL_ERROR "NT2 requires a recent version of Boost but none recent enough was found")
endif()

################################################################################
# Module inclusion
################################################################################
set(NT2_MODULES_EXTRA "" CACHE STRING "Extra modules to load")
set(NT2_MODULES_BLACKLIST "" CACHE STRING "Modules that should not be loaded")

################################################################################
# We search a directory under modules/ for which a CMakeLists.txt is present;
# if none is found in the directory, we search recursively until we find one.
################################################################################
macro(expand_submodules modules)
  set(i 0)
  list(LENGTH ${modules} len)
  while(i LESS len)
    list(GET ${modules} ${i} module)
    string(REPLACE "." "/" module_path ${module})
    if(${module} MATCHES boostification)
      list(REMOVE_ITEM ${modules} ${module})
      list(LENGTH ${modules} len)
    elseif(NOT EXISTS ${PROJECT_SOURCE_DIR}/modules/${module_path}/CMakeLists.txt)
      list(REMOVE_ITEM ${modules} ${module})
      file(GLOB ${modules}_ RELATIVE ${PROJECT_SOURCE_DIR}/modules ${PROJECT_SOURCE_DIR}/modules/${module_path}/*/)
      if(${modules}_)
        string(REPLACE "/" "." ${modules}_ "${${modules}_}")
        list(APPEND ${modules} ${${modules}_})
      endif()
      list(LENGTH ${modules} len)
    else()
      math(EXPR i "${i} + 1")
    endif()
  endwhile()
endmacro()

macro(remove_blacklisted modules)
  set(${modules}_)
  foreach(module ${${modules}})
    set(module_found 1)
    foreach(bl ${NT2_MODULES_BLACKLIST})
      if(${module} MATCHES "^${bl}($|\\.)")
        set(module_found 0)
      endif()
    endforeach()
    if(module_found)
      list(APPEND ${modules}_ ${module})
    endif()
  endforeach()
  set(${modules} ${${modules}_})
endmacro()

################################################################################
# If no explicit modules are set, we use all modules we can find
################################################################################
if(NOT NT2_MODULES)
  file(GLOB NT2_MODULES RELATIVE ${PROJECT_SOURCE_DIR}/modules ${PROJECT_SOURCE_DIR}/modules/*/)
endif()
expand_submodules(NT2_MODULES)
remove_blacklisted(NT2_MODULES)

################################################################################
# Download extra modules
################################################################################
include(nt2.download)
list(REMOVE_DUPLICATES NT2_MODULES_EXTRA)
remove_blacklisted(NT2_MODULES_EXTRA)
foreach(module ${NT2_MODULES_EXTRA})
    string(REPLACE "." "/" module_path ${module})

    if(NOT IS_DIRECTORY ${PROJECT_SOURCE_DIR}/modules/${module_path})
      nt2_download_module(${module})
    endif()
endforeach()
expand_submodules(NT2_MODULES_EXTRA)
remove_blacklisted(NT2_MODULES_EXTRA)
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
# Load modules
################################################################################
foreach(module ${NT2_MODULES})
  string(REPLACE "." "/" module_path ${module})
  if(NOT IS_DIRECTORY ${PROJECT_SOURCE_DIR}/modules/${module_path})
    message(STATUS "[nt2] module ${module} not found")
  else()
    message(STATUS "[nt2] loading module ${module}")
    add_subdirectory(modules/${module_path})
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
