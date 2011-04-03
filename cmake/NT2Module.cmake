################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

macro(nt2_str_remove_duplicates)
  foreach(str ${ARGV})
    string(REPLACE "  " " " str_ws ${${str}})
    string(REPLACE " " ";" str_list ${str_ws})
    if(str_list)
      list(REMOVE_DUPLICATES str_list)
    endif()
    string(REPLACE ";" " " str_new "${str_list}")
    if(NOT str_new)
      set(str_new " ")
    endif()
    set(${str} ${str_new})
  endforeach()
endmacro()

macro(nt2_module_install_setup)
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
endmacro()

macro(nt2_module_source_setup module)
  nt2_module_install_setup()
  string(TOUPPER ${module} module_U)
  
  set(NT2_CURRENT_MODULE ${module})
  set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
  
  include_directories(${NT2_${module_U}_INCLUDE_DIR})
  link_directories(${NT2_${module_U}_DEPENDENCIES_LIBRARY_DIR})
  link_libraries(${NT2_${module_U}_DEPENDENCIES_LIBRARIES})
  
  set(NT2_CURRENT_FLAGS "${NT2_CURRENT_FLAGS} ${NT2_${module_U}_DEPENDENCIES_FLAGS}")
  nt2_str_remove_duplicates(NT2_CURRENT_FLAGS)
endmacro()

macro(nt2_setup_variant)
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
  elseif(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DNT2_DEBUG")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DNT2_DEBUG")
  endif()
endmacro()

macro(nt2_module_main module)
  string(TOUPPER ${module} module_U)
  
  set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
  set(NT2_${module_U}_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
  
  if(NOT NT2_${module_U}_FOUND)
  
    # load dependencies
    #message(STATUS "[nt2.${module}] checking dependencies...")
    include(nt2.${module}.dependencies OPTIONAL)
    
    if(DEFINED NT2_${module_U}_DEPENDENCIES_FOUND AND NOT NT2_${module_U}_DEPENDENCIES_FOUND)
      message(WARNING "[nt2.${module}] dependencies not met, skipping module")
      nt2_find_transfer_parent()
      return()
    endif()
    
    # set FindNT2 variables
    set(NT2_${module_U}_FOUND 1)
    set(NT2_${module_U}_INCLUDE_DIR ${PROJECT_BINARY_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include ${NT2_${module_U}_DEPENDENCIES_INCLUDE_DIR})
    set(NT2_${module_U}_LIBRARY_DIR ${PROJECT_BINARY_DIR}/lib ${NT2_${module_U}_DEPENDENCIES_LIBRARY_DIR})
    set(NT2_${module_U}_LIBRARIES ${NT2_${module_U}_DEPENDENCIES_LIBRARIES} ${NT2_${module_U}_LIBRARIES})
    set(NT2_${module_U}_FLAGS "${NT2_${module_U}_DEPENDENCIES_FLAGS} ${NT2_${module_U}_FLAGS}")
    set(NT2_FOUND_COMPONENTS ${module} ${NT2_FOUND_COMPONENTS})
         
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
      add_subdirectory(src)
    endif()
    
  endif()
  
  set(NT2_CURRENT_MODULE ${module})
  nt2_setup_variant()
  
  # set include/link directories
  include_directories(${NT2_${module_U}_INCLUDE_DIR})
  link_directories(${NT2_${module_U}_LIBRARY_DIR})
  link_libraries(${NT2_${module_U}_LIBRARIES})
  
  set(NT2_CURRENT_FLAGS "${NT2_CURRENT_FLAGS} ${NT2_${module_U}_FLAGS}")
  nt2_str_remove_duplicates(NT2_CURRENT_FLAGS)
  
  nt2_module_install_setup()
  
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

  if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bench)
    add_custom_target(${module}.bench)
    add_subdirectory(bench)
  endif()
  
  if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/examples)
    add_custom_target(${module}.examples)
    add_subdirectory(examples)
  endif()
  
  if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/unit)
    add_custom_target(${module}.unit)
    add_subdirectory(unit)
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
    add_library(${libname} ${ARGN})
  endif()

  set_target_properties(${libname} PROPERTIES VERSION 3.0.0 SOVERSION 3)
  
  set_property(TARGET ${libname} PROPERTY COMPILE_FLAGS "${NT2_CURRENT_FLAGS} -DNT2_${NT2_CURRENT_MODULE_U}_SOURCE")
  
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
  link_libraries(${NT2_LIBRARIES})
  
  set(NT2_CURRENT_FLAGS "${NT2_CURRENT_FLAGS} ${NT2_FLAGS}")
  nt2_str_remove_duplicates(NT2_CURRENT_FLAGS)
  
  nt2_find_transfer_parent()
endmacro()

macro(nt2_module_add_exe DIRECTORY EXECUTABLE)
  string(TOUPPER ${NT2_CURRENT_MODULE} NT2_CURRENT_MODULE_U)

  add_executable(${EXECUTABLE} EXCLUDE_FROM_ALL ${ARGN})
  
  set_property(TARGET ${EXECUTABLE} PROPERTY COMPILE_FLAGS ${NT2_CURRENT_FLAGS})
  set_property(TARGET ${EXECUTABLE} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${DIRECTORY})
endmacro()

macro(nt2_module_add_unit EXECUTABLE)
  nt2_module_add_exe(unit ${EXECUTABLE} ${ARGN})

  string(REGEX REPLACE "\\.([^.]+)\\.unit$" ".unit" suite ${EXECUTABLE})
  string(REGEX REPLACE "\\.unit$" "-unit" TEST ${EXECUTABLE})
  
  add_dependencies(${suite} ${EXECUTABLE})
  add_test(${TEST} ${PROJECT_BINARY_DIR}/unit/${EXECUTABLE})
endmacro()

macro(nt2_module_add_bench EXECUTABLE)
  nt2_module_add_exe(bench ${EXECUTABLE} ${ARGN})

  string(REGEX REPLACE "\\.([^.]+)\\.bench$" ".bench" suite ${EXECUTABLE})
  
  add_dependencies(${suite} ${EXECUTABLE})
endmacro()

macro(nt2_module_add_example EXECUTABLE)
  nt2_module_add_exe(examples ${EXECUTABLE} ${ARGN})

  string(REGEX REPLACE "\\.([^.]+)\\.sample$" ".examples" suite ${EXECUTABLE})
  
  add_dependencies(${suite} ${EXECUTABLE})
endmacro()
