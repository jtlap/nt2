################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

# set up installation directories
if(NOT UNIX)
  set( NT2_INSTALL_SHARE_DIR
       ${CMAKE_INSTALL_PREFIX}
       CACHE PATH "The directory where we install the extra files that are not headers nor libraries"
       FORCE
     )
else()
  set( NT2_INSTALL_SHARE_DIR ${CMAKE_INSTALL_PREFIX}/share/nt2
       CACHE PATH "The directory where we install the extra files that are not headers nor libraries"
       FORCE
     )
endif()

set( NT2_INSTALL_INCLUDE_DIR
     ${CMAKE_INSTALL_PREFIX}/include
     CACHE PATH "The directory where we install the header files"
     FORCE
   )
   
set( NT2_INSTALL_LIBRARY_DIR
     ${CMAKE_INSTALL_PREFIX}/lib
     CACHE PATH "The directory where we install the libraries"
     FORCE
   )

macro(nt2_module_source_setup module)
  string(TOUPPER ${module} module_U)

  set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
  include_directories( ${PROJECT_BINARY_DIR}/include
                       ${NT2_${module_U}_INCLUDE_DIR}
                     )
  link_directories(${NT2_${module_U}_LIBRARY_DIR})
endmacro()

macro(nt2_module_main module)
  string(TOUPPER ${module} module_U)
  
  # load dependencies
  set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
  set(NT2_${module_U}_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
  
  #message(STATUS "[nt2.${module}] checking dependencies...")
  include(nt2.${module}.dependencies)
  
  if(NOT NT2_${module_U}_DEPENDENCIES_FOUND)
    message(WARNING "[nt2.${module}] dependencies not met, skipping module")
    nt2_find_transfer_parent()
    return()
  endif()
  
  # set FindNT2 variables
  set(NT2_CURRENT_MODULE ${module})
  set(NT2_${module_U}_FOUND 1)
  set(NT2_${module_U}_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include ${NT2_${module_U}_DEPENDENCIES_INCLUDE_DIR})
  set(NT2_${module_U}_LIBRARY_DIR ${PROJECT_BINARY_DIR}/lib ${NT2_${module_U}_DEPENDENCIES_LIBRARY_DIR})
  set(NT2_${module_U}_LIBRARIES ${NT2_${module_U}_DEPENDENCIES_LIBRARIES} ${NT2_${module_U}_LIBRARIES})
  set(NT2_${module_U}_FLAGS "${NT2_${module_U}_DEPENDENCIES_FLAGS} ${NT2_${module_U}_FLAGS}")
  set(NT2_FOUND_COMPONENTS ${module} ${NT2_FOUND_COMPONENTS})
  
  # set include/link directories
  nt2_module_source_setup(${module})
     
  # install headers, cmake modules and manifest
  install( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
           DESTINATION ${NT2_INSTALL_INCLUDE_DIR}
           COMPONENT ${NT2_CURRENT_MODULE}
           FILES_MATCHING PATTERN "*.hpp"
         )
  install( DIRECTORY ${PROJECT_BINARY_DIR}/include/
           DESTINATION ${NT2_INSTALL_INCLUDE_DIR}
           COMPONENT ${NT2_CURRENT_MODULE}
           FILES_MATCHING PATTERN "*.hpp"
         )
  file(WRITE ${PROJECT_BINARY_DIR}/modules/sdk.manifest)
  install( FILES ${PROJECT_BINARY_DIR}/modules/sdk.manifest
           DESTINATION ${NT2_INSTALL_SHARE_DIR}/modules
           COMPONENT ${NT2_CURRENT_MODULE}
         )
  install( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cmake
           DESTINATION ${NT2_INSTALL_SHARE_DIR}
           COMPONENT ${NT2_CURRENT_MODULE}
           FILES_MATCHING PATTERN "*.cmake"
         )
       
  if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
    add_subdirectory(src)
  endif()

  if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bench)
    add_custom_target(${module}.bench)
    add_subdirectory(bench EXCLUDE_FROM_ALL)
  endif()
  
  if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/examples)
    add_custom_target(${module}.examples)
    add_subdirectory(examples EXCLUDE_FROM_ALL)
  endif()
  
  if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/unit)
    add_custom_target(${module}.unit)
    add_subdirectory(unit EXCLUDE_FROM_ALL)
  endif()
  
  nt2_find_transfer_parent()
endmacro()

macro(nt2_module_add_library libname)
  string(TOUPPER ${NT2_CURRENT_MODULE} NT2_CURRENT_MODULE_U)
  
  if(DEFINED NT2_USE_STATIC_LIBS AND NOT DEFINED NT2_${NT2_CURRENT_MODULE_U}_USE_STATIC_LIBS)
    set(NT2_${NT2_CURRENT_MODULE_U}_USE_STATIC_LIBS NT2_USE_STATIC_LIBS)
  endif()

  if(DEFINED NT2_${NT2_CURRENT_MODULE_U}_USE_STATIC_LIBS)
    if(NT2_${NT2_CURRENT_MODULE_U}_USE_STATIC_LIBS)
      add_library(${libname} SHARED ${ARGN})
    else()
      add_library(${libname} STATIC ${ARGN})
    endif()
  else()
    add_library(${libname} ${source_files})
  endif()

  set_target_properties(${libname} PROPERTIES VERSION 3.0.0 SOVERSION 3)

  install( TARGETS ${libname}
           LIBRARY DESTINATION ${NT2_INSTALL_LIBRARY_DIR}
           ARCHIVE DESTINATION ${NT2_INSTALL_LIBRARY_DIR}
           COMPONENT ${NT2_CURRENT_MODULE}
         )
  
endmacro()

macro(nt2_module_use_modules component)
  #message(STATUS "[nt2.${NT2_CURRENT_MODULE}] ${component}: checking dependencies...")
  
  find_package(NT2 COMPONENTS ${ARGN})
  if(NOT NT2_FOUND)
    message(WARNING "[nt2.${NT2_CURRENT_MODULE}] ${component}: dependencies not met, skipping")
    nt2_find_transfer_parent()
    return()
  endif()

  include_directories(${NT2_INCLUDE_DIR})
  link_directories(${NT2_LIBRARY_DIR})
  
  nt2_find_transfer_parent()
endmacro()

macro(nt2_module_add_unit EXECUTABLE)
  string(TOUPPER ${NT2_CURRENT_MODULE} NT2_CURRENT_MODULE_U)

  string(REGEX REPLACE "\\.([^.]+)\\.unit$" ".unit" suite ${EXECUTABLE})
  string(REGEX REPLACE "\\.unit$" "-unit" TEST ${EXECUTABLE})

  add_executable(${EXECUTABLE} ${ARGN})
  set_property(TARGET ${EXECUTABLE} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/unit)
  target_link_libraries(${EXECUTABLE} ${NT2_${NT2_CURRENT_MODULE_U}_LIBRARIES})
  set_target_properties(${EXECUTABLE} PROPERTIES COMPILE_FLAGS ${NT2_${NT2_CURRENT_MODULE_U}_FLAGS})
  
  add_test(${TEST} ${PROJECT_BINARY_DIR}/unit/${EXECUTABLE})
  add_dependencies(${suite} ${EXECUTABLE})
endmacro()
