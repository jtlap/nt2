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
set(NT2_SDK_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
include(nt2.sdk.dependencies)
if(NOT NT2_SDK_DEPENDENCIES_FOUND)
  message(WARNING "[nt2.sdk] dependencies not met, skipping module")
  return()
endif()
set(NT2_CURRENT_MODULE sdk)

include_directories( ${PROJECT_BINARY_DIR}/include
                     ${CMAKE_CURRENT_SOURCE_DIR}/include
                     ${NT2_SDK_DEPENDENCIES_INCLUDE_DIR}
                   )

set( NT2_INSTALL_DIR
     ${CMAKE_INSTALL_PREFIX}/share/nt2
     CACHE PATH "The directory where we install the extra files that are not headers nor libraries"
     FORCE
   )

set( NT2_INCLUDE_INSTALL_DIR
     ${CMAKE_INSTALL_PREFIX}/include
     CACHE PATH "The directory where we install the header files"
     FORCE
   )
   
set( NT2_LIBRARY_INSTALL_DIR
     ${CMAKE_INSTALL_PREFIX}/lib
     CACHE PATH "The directory where we install the libraries"
     FORCE
   )

add_subdirectory(src)
install( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
         DESTINATION ${NT2_INCLUDE_INSTALL_DIR}
         FILES_MATCHING PATTERN "*.hpp"
       )
file(WRITE ${PROJECT_BINARY_DIR}/modules/sdk.manifest)
install( FILES ${PROJECT_BINARY_DIR}/modules/sdk.manifest
         DESTINATION ${NT2_INSTALL_DIR}/modules/sdk.manifest
       )
install( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cmake
         DESTINATION ${NT2_INSTALL_DIR}/cmake
         FILES_MATCHING PATTERN "*.cmake"
         
       )

add_subdirectory(bench EXCLUDE_FROM_ALL)

find_package(NT2 COMPONENTS predicates)
if(NT2_FOUND)
  include_directories( ${NT2_PREDICATES_INCLUDE_DIR} )
  add_subdirectory(examples EXCLUDE_FROM_ALL)
endif()

add_subdirectory(unit EXCLUDE_FROM_ALL)

nt2_find_transfer_parent()
