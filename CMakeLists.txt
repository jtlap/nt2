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
# Enable testing if using Makefile generator or instructed to do so
################################################################################
if(CMAKE_GENERATOR MATCHES "Make" OR NT2_WITH_TESTS)
  ENABLE_TESTING()
endif()

################################################################################
# Module inclusion
################################################################################
set(NT2_SOURCE_ROOT ${PROJECT_SOURCE_DIR})

if(NOT NT2_MODULES)
  file(GLOB NT2_MODULES RELATIVE ${PROJECT_SOURCE_DIR}/modules ${PROJECT_SOURCE_DIR}/modules/*/)
  foreach(${module} NT2_MODULES)
    if(NOT EXISTS ${PROJECT_SOURCE_DIR}/modules/${module}/CMakeLists.txt)
      list(REMOVE_ITEM NT2_MODULES ${module})
    endif()
  endforeach()
endif()
if(NT2_MODULES_EXTRA)
  list(APPEND NT2_MODULES ${NT2_MODULES_EXTRA})
  list(REMOVE_DUPLICATES ${NT2_MODULES})
endif()

include(nt2.download)
foreach(module ${NT2_MODULES})
  list(FIND NT2_MODULES_BLACKLIST ${module} module_found)
  if(module_found LESS 0)
  
    if(NOT IS_DIRECTORY ${PROJECT_SOURCE_DIR}/modules/${module})
      nt2_download_module(${module})
    endif()
  
    if(NOT IS_DIRECTORY ${PROJECT_SOURCE_DIR}/modules/${module})
      message(STATUS "[nt2] module ${module} not found")
    else()
      message(STATUS "[nt2] loading module ${module}")
      add_subdirectory(modules/${module})
    endif()
    
  endif()
endforeach()

ADD_SUBDIRECTORY(sandbox)

################################################################################
# Post-config message
################################################################################
INCLUDE(nt2.directive) 
