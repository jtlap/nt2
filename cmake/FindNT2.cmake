################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

# The following script can used to find NT2 modules, be it installations or source.
# Passing no component results in all modules being searched for.
#
# It defines the following variables, with COMPONENT_U being a component set to uppercase:
# - NT2_${COMPONENT_U}_FOUND        boolean that tells whether the associated component
#                                   and all of its dependencies were found.
# - NT2_FOUND                       boolean that tells whether all the requested components
#                                   were found.
# - NT2_${COMPONENT_U}_INCLUDE_DIR  list of directories that are necessary to add to the INCLUDE_PATH
#                                   to use the component
# - NT2_INCLUDE_DIR                 list of directories that are necessary to add to the INCLUDE_PATH
#                                   to use all the requested components
# - NT2_${COMPONENT_U}_LIBRARY_DIR  list of directories that are necessary to add to the LIBRARY_PATH
#                                   to use the component
# - NT2_LIBRARY_DIR                 list of directories that are necessary to add to the LIBRARY_PATH
#                                   to use all the requested components
# - NT2_${COMPONENT_U}_LIBRARIES    list of libraries that are necessary to link to use the component
# - NT2_LIBRARIES                   list of libraries that are necessary to link all the requested components
# - NT2_${COMPONENT_U}_FLAGS        flags that must be passed to the compiler to use the component
# - NT2_FLAGS                       flags that must be passed to the compiler to use all the requested components
# - NT2_FOUND_COMPONENTS            list of components that were found, including their dependencies.
#
# Additionally, the script also adds all the NT2-specific CMake modules to the CMAKE_MODULE_PATH.
#
# You can set the following variables to help the script:
# - NT2_ROOT                        root of the NT2 installation or "share" directory
# - NT2_INCLUDE_ROOT                root of the includes of a NT2 installation (defaults to NT2_ROOT/include)
# - NT2_SOURCE_ROOT                 root of the NT2 source 
# - NT2_CURRENT_MODULE              current module being compiled, can be used to avoid self-dependencies
#                                   when compiling a NT2 module

macro(nt2_copy_parent)
  foreach(ARG ${ARGV})
    set(${ARG} ${${ARG}} PARENT_SCOPE)
  endforeach()
endmacro()

function(nt2_find_log)
  if(DEFINED NT2_FIND_VERBOSE OR DEFINED ENV{NT2_FIND_VERBOSE})
    message(STATUS "[FindNT2]${NT2_FIND_RECURSIVE}${ARGV}")
  endif()
endfunction()

function(nt2_find_warning)
  message(WARNING "[FindNT2]${NT2_FIND_RECURSIVE}${ARGV}")
endfunction()

macro(nt2_find_module_dependencies)
  if(NOT NT2_CURRENT_MODULE STREQUAL COMPONENT)
    include("nt2.${COMPONENT}.dependencies" OPTIONAL)
  endif()
    
  if(NOT DEFINED NT2_${COMPONENT_U}_DEPENDENCIES_FOUND)
    set(NT2_${COMPONENT_U}_FOUND 1)
  elseif(NT2_${COMPONENT_U}_DEPENDENCIES_FOUND)
    set(NT2_${COMPONENT_U}_FOUND 1)
  else()
    set(NT2_${COMPONENT_U}_FOUND 0)
  endif()
    
  if(NOT NT2_${COMPONENT_U}_FOUND)
    nt2_find_log("${COMPONENT} dependencies not met")
  endif()
endmacro()

macro(nt2_remove_duplicates)
  foreach(ARG ${ARGV})
    if(ARG)
      list(REMOVE_DUPLICATES ARG)
    endif()
  endforeach()
endmacro()

macro(nt2_find_module_return)
  nt2_remove_duplicates( NT2_${COMPONENT_U}_INCLUDE_DIR NT2_${COMPONENT_U}_LIBRARY_DIR
                         NT2_${COMPONENT_U}_LIBRARIES
                       )
    
  nt2_find_log("variables for module ${COMPONENT}")
  nt2_find_log("-- NT2_${COMPONENT_U}_FOUND = ${NT2_${COMPONENT_U}_FOUND}")
  nt2_find_log("-- NT2_${COMPONENT_U}_INCLUDE_DIR = ${NT2_${COMPONENT_U}_INCLUDE_DIR}")
  nt2_find_log("-- NT2_${COMPONENT_U}_LIBRARY_DIR = ${NT2_${COMPONENT_U}_LIBRARY_DIR}")
  nt2_find_log("-- NT2_${COMPONENT_U}_LIBRARIES = ${NT2_${COMPONENT_U}_LIBRARIES}")
  nt2_find_log("-- NT2_${COMPONENT_U}_FLAGS = ${NT2_${COMPONENT_U}_FLAGS}")
    
  nt2_copy_parent( NT2_${COMPONENT_U}_FOUND
                   NT2_${COMPONENT_U}_INCLUDE_DIR NT2_${COMPONENT_U}_LIBRARY_DIR
                   NT2_${COMPONENT_U}_LIBRARIES NT2_${COMPONENT_U}_FLAGS
                 )
                   
  set(NT2_${COMPONENT_U}_FOUND_COMPONENTS ${NT2_FOUND_COMPONENTS} PARENT_SCOPE)
  return()
endmacro()

function(nt2_find_module COMPONENT)
  
  string(TOUPPER ${COMPONENT} COMPONENT_U)
  
  if(NT2_${COMPONENT_U}_FOUND)
    nt2_find_log("${COMPONENT} already found")
    return()
  endif()
  
  # Search for module source
  if(NOT NT2_${COMPONENT_U}_ROOT)
    find_file( NT2_${COMPONENT_U}_ROOT ${COMPONENT}
               PATHS ${NT2_SOURCE_ROOT}/modules
               NO_DEFAULT_PATH
               ENV NT2_${COMPONENT_U}_ROOT
             )
  endif()
    
  # Source found
  if(NT2_CURRENT_MODULE STREQUAL COMPONENT OR NT2_${COMPONENT_U}_ROOT)
    if(NT2_CURRENT_MODULE STREQUAL COMPONENT)
      nt2_find_log("${COMPONENT} being built")
    else()
      nt2_find_log("${COMPONENT} source found, testing dependencies")
      set(CMAKE_MODULE_PATH "${NT2_${COMPONENT_U}_ROOT}/cmake" ${CMAKE_MODULE_PATH})
    endif()
    
    nt2_find_module_dependencies()
    
    set(NT2_${COMPONENT_U}_INCLUDE_DIR ${PROJECT_BINARY_DIR}/include ${NT2_${COMPONENT_U}_ROOT}/include ${NT2_${COMPONENT_U}_DEPENDENCIES_INCLUDE_DIR})
    set(NT2_${COMPONENT_U}_LIBRARY_DIR ${PROJECT_BINARY_DIR}/lib ${NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARY_DIR})
    set(NT2_${COMPONENT_U}_LIBRARIES ${NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARIES} ${NT2_${COMPONENT_U}_LIBRARIES})
    set(NT2_${COMPONENT_U}_FLAGS "${NT2_${COMPONENT_U}_DEPENDENCIES_FLAGS} ${NT2_${COMPONENT_U}_FLAGS}")
    
    if(NOT NT2_CURRENT_MODULE STREQUAL COMPONENT)
      if(IS_DIRECTORY ${NT2_${COMPONENT_U}_ROOT}/src)
        add_subdirectory(${NT2_${COMPONENT_U}_ROOT}/src ${PROJECT_BINARY_DIR}/modules/${COMPONENT}/src)
      endif()
    endif()
    
    nt2_find_module_return()
  endif()
    
  # Look for module in install
  if(NT2_ROOT)
    if(NOT EXISTS ${NT2_ROOT}/modules/${COMPONENT}.manifest)
      nt2_find_log("${COMPONENT} not found in nt2 install")
      set(NT2_${COMPONENT_U}_FOUND 0)
      nt2_find_module_return()
    endif()
    
    nt2_find_log("${COMPONENT} install found, testing dependencies")
    nt2_find_module_dependencies()
      
    set(NT2_${COMPONENT_U}_INCLUDE_DIR ${NT2_${COMPONENT_U}_DEPENDENCIES_INCLUDE_DIR} ${NT2_INCLUDE_ROOT})
    set(NT2_${COMPONENT_U}_LIBRARY_DIR ${NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARY_DIR})
      
    foreach(LIBRARY ${NT2_${COMPONENT_U}_LIBRARIES})
      find_library(LIBRARY_PATH ${NT2_ROOT}/lib)
      list(APPEND NT2_${COMPONENT_U}_LIBRARY_DIR ${LIBRARY_PATH})
    endforeach()
    set(NT2_${COMPONENT_U}_LIBRARIES ${NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARIES} ${NT2_${COMPONENT_U}_LIBRARIES})
    
    set(NT2_${COMPONENT_U}_FLAGS "${NT2_${COMPONENT_U}_DEPENDENCIES_FLAGS} ${NT2_${COMPONENT_U}_FLAGS}")

    nt2_find_module_return()
  endif()      

  # No source nor install
  nt2_find_log("can't find ${COMPONENT} in source nor install")
  set(NT2_${COMPONENT_U}_FOUND 0)

  nt2_find_module_return()
    
endfunction()

macro(nt2_prepend_module name)
  set(NT2_${name} ${NT2_${COMPONENT_U}_${name}} ${NT2_${name}})
  if(NT2_${name})
    list(REMOVE_DUPLICATES NT2_${name})
  endif()
endmacro()

macro(nt2_flag_found)
  foreach(COMPONENT_ ${NT2_FOUND_COMPONENTS})
    string(TOUPPER ${COMPONENT_} COMPONENT_U_)
    nt2_copy_parent( NT2_${COMPONENT_U_}_FOUND
                     NT2_${COMPONENT_U_}_INCLUDE_DIR NT2_${COMPONENT_U_}_LIBRARY_DIR
                     NT2_${COMPONENT_U_}_LIBRARIES NT2_${COMPONENT_U_}_FLAGS
                   )
  endforeach()
endmacro()

macro(nt2_find_transfer_parent)
  if(NOT ${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    nt2_flag_found()
  endif()
  nt2_copy_parent(NT2_FOUND_COMPONENTS)
endmacro()

function(nt2_find)

  set(NT2_FOUND 1)
  set(NT2_INCLUDE_DIR "")
  set(NT2_LIBRARY_DIR "")
  set(NT2_LIBRARIES "")
  set(NT2_FLAGS " ")
  set(NT2_FOUND_COMPONENTS ${NT2_FOUND_COMPONENTS})
  
  if(DEFINED NT2_FIND_RECURSIVE)
    set(NT2_FIND_RECURSIVE_ "${NT2_FIND_RECURSIVE_}  ")
    set(NT2_FIND_RECURSIVE "${NT2_FIND_RECURSIVE_} \\_ ")
  else()
    set(NT2_FIND_RECURSIVE " ")
  endif()
  if(NOT DEFINED NT2_CURRENT_MODULE)
      set(NT2_CURRENT_MODULE " ")
  endif()

  # Search for source
  if(NOT NT2_SOURCE_ROOT AND DEFINED ENV{NT2_SOURCE_ROOT})
    nt2_find_log("found NT2 source root ${NT2_SOURCE_ROOT}")
    set(NT2_SOURCE_ROOT $ENV{NT2_SOURCE_ROOT})
  endif()
    
  # Search for install
  if(NOT NT2_ROOT)
    find_file ( NT2_ROOT nt2
                PATHS /Applications
                      /usr/local/share /usr/share /opt
                      "C:\\Program Files"
                ENV NT2_ROOT
                NO_DEFAULT_PATH
              )
    if(NT2_ROOT)
      nt2_find_log("found NT2 root ${NT2_ROOT}")
    endif()
  endif()
  if(NT2_ROOT)
    set(CMAKE_MODULE_PATH ${NT2_ROOT}/cmake ${CMAKE_MODULE_PATH})
    
    if(NOT NT2_INCLUDE_ROOT)
      find_path ( NT2_INCLUDE_ROOT nt2
                  PATHS ${NT2_ROOT}/include
                        /usr/local/include /usr/include
                  ENV NT2_INCLUDE_ROOT
                )
      if(NOT NT2_INCLUDE_ROOT)
        nt2_find_warning("could find install but not include path, bad install?")
      else()
        nt2_find_log("found NT2 include root ${NT2_INCLUDE_ROOT}")
      endif()
    endif()
  endif()
  
  # if no component specified, we glob the source or install directories for modules
  if(ARGC EQUAL 0)
    if(NT2_SOURCE_ROOT)
      file(GLOB NT2_COMPONENTS_ROOT ${NT2_SOURCE_ROOT}/modules/*/)
      foreach(NT2_COMPONENT ${NT2_COMPONENTS_ROOT})
        if(IS_DIRECTORY ${NT2_COMPONENT})
          string(REGEX REPLACE "^.*/(.*)$" "\\1" NT2_COMPONENT ${NT2_COMPONENT})
          list(APPEND NT2_COMPONENTS ${NT2_COMPONENT})
        endif()
      endforeach()
    elseif(NT2_ROOT)
      file(GLOB NT2_COMPONENTS_ROOT ${NT2_ROOT}/modules/*.manifest)
      foreach(NT2_COMPONENT ${NT2_COMPONENTS_ROOT})
        string(REGEX REPLACE "^.*/(.*)\\.manifest$" "\\1" NT2_COMPONENT ${NT2_COMPONENT})
        list(APPEND NT2_COMPONENTS ${NT2_COMPONENT})
      endforeach()
    else()
      set(NT2_FOUND 0)
    endif()
    if(NT2_COMPONENTS)
      nt2_find(${NT2_COMPONENTS})
      nt2_flag_found()
      return()
    endif()
  endif()

  foreach(COMPONENT ${ARGV})
    string(TOUPPER ${COMPONENT} COMPONENT_U)
    nt2_find_module(${COMPONENT})
    if(NT2_FOUND AND NT2_${COMPONENT_U}_FOUND)
        set(NT2_FOUND_COMPONENTS ${COMPONENT} ${NT2_FOUND_COMPONENTS})
    else()
        set(NT2_FOUND 0)
    endif()
    nt2_prepend_module(INCLUDE_DIR)
    nt2_prepend_module(LIBRARY_DIR)
    nt2_prepend_module(LIBRARIES)
    nt2_prepend_module(FOUND_COMPONENTS)
    
    set(NT2_FLAGS "${NT2_${COMPONENT_U}_FLAGS} ${NT2_FLAGS}")
    
    nt2_flag_found()
  endforeach()
  
  nt2_copy_parent( NT2_FOUND
                   NT2_INCLUDE_DIR NT2_LIBRARY_DIR
                   NT2_LIBRARIES NT2_FLAGS
                   NT2_FOUND_COMPONENTS
                 )

endfunction()

nt2_find(${NT2_FIND_COMPONENTS})
if(NT2_FIND_RECURSIVE)
  nt2_flag_found()
endif()
