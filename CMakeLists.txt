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
set(CPACK_PACKAGE_NAME "NT2")
set(CPACK_PACKAGE_VENDOR "Metascale")
set(CPACK_PACKAGE_CONTACT "Metascale <contact@metascale.org>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Numerical Template Toolbox")

set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.rst")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.rst")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

set(CPACK_PACKAGE_VERSION_MAJOR "3")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

set(NT2_VERSION_NUMBER "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(NT2_VERSION ${NT2_VERSION_NUMBER})

set(CPACK_PACKAGE_FILE_NAME "nt2-${NT2_VERSION}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY nt2)

# NSIS-specific
set(CPACK_PACKAGE_ICON "${PROJECT_SOURCE_DIR}/doc/source\\\\nt2.png")
set(CPACK_NSIS_DISPLAY_NAME "NT2 - Numerical Template Toolbox")
set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\nt2.metascale.org")
set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\nt2.metascale.org")
set(CPACK_NSIS_CONTACT "contact@metascale.org")

set(CPACK_STRIP_FILES 1)
set(CPACK_SOURCE_STRIP_FILES 1)
set(CPACK_COMPONENTS_ALL_IN_ONE_PACKAGE 1)

include(CPack)

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
ENABLE_TESTING()
ADD_CUSTOM_TARGET( bench
                   WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/bench
                 )
ADD_CUSTOM_TARGET( examples
                   WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/examples
                 )
ADD_CUSTOM_TARGET( unit
                   WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/unit
                 )
ADD_CUSTOM_TARGET( cover
                   WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/cover
                 )

################################################################################
# Module inclusion
################################################################################

macro(nt2_load_module module)
  add_subdirectory(${PROJECT_SOURCE_DIR}/modules/${module})
  add_dependencies(bench ${module}.bench)
  add_dependencies(examples ${module}.examples)
  add_dependencies(unit ${module}.unit)
  add_dependencies(cover ${module}.cover)
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
