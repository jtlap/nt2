################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

# This script defines the following variables, with ${COMPONENT_U} being a component
# set to uppercase:
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
# - NT2_FOUND_COMPONENTS            list of components that were found, including their dependencies.
#
# Additionally, the script also adds all the NT2-specific CMake modules to the CMAKE_MODULE_PATH.
#
# When searching for a NT2 module within another NT2 module, with the former depending on the latter, set
# the NT2_CURRENT_MODULE variable to the current module (lowercase) to avoid circular dependencies.

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

function(nt2_find COMPONENT)
  
  string(TOUPPER ${COMPONENT} COMPONENT_U)
  
  if(NT2_${COMPONENT_U}_FOUND)
    nt2_find_log("${COMPONENT} already found")
    return()
  endif()
  
  # Search for installation
  # TODO
  
  # Search for source
  if(NOT DEFINED NT2_MODULAR_ROOT AND DEFINED ENV{NT2_${COMPONENT_U}_ROOT})
    set(NT2_${COMPONENT_U}_ROOT $ENV{NT2_${COMPONENT_U}_ROOT})
  elseif(DEFINED NT2_MODULAR_ROOT)
    set(NT2_${COMPONENT_U}_ROOT "${NT2_MODULAR_ROOT}/modules/${COMPONENT}")
  endif()
    
  if(DEFINED NT2_${COMPONENT_U}_ROOT)
    
    if(${NT2_CURRENT_MODULE} STREQUAL ${COMPONENT})
      nt2_find_log("${COMPONENT} being built")
    else()
      nt2_find_log("${COMPONENT} found, testing dependencies")
    
      set(CMAKE_MODULE_PATH "${NT2_${COMPONENT_U}_ROOT}/cmake" ${CMAKE_MODULE_PATH})
      find_file(NT2_${COMPONENT_U}_DEPENDENCIES_FILE "nt2.${COMPONENT}.dependencies.cmake" ${CMAKE_MODULE_PATH})
      if(NOT ${NT2_${COMPONENT_U}_DEPENDENCIES_FILE} MATCHES "NOTFOUND")
        include(${NT2_${COMPONENT_U}_DEPENDENCIES_FILE})
      endif()
    endif()
    
    if(NOT DEFINED NT2_${COMPONENT_U}_DEPENDENCIES_FOUND)
      set(NT2_${COMPONENT_U}_FOUND 1)
    elseif(NT2_${COMPONENT_U}_DEPENDENCIES_FOUND)
      set(NT2_${COMPONENT_U}_FOUND 1)
    else()
      set(NT2_${COMPONENT_U}_FOUND 0)
    endif()
    set(NT2_${COMPONENT_U}_INCLUDE_DIR ${NT2_${COMPONENT_U}_DEPENDENCIES_INCLUDE_DIR} "${NT2_${COMPONENT_U}_ROOT}/include")
    if(NT2_${COMPONENT_U}_INCLUDE_DIR)
      list(REMOVE_DUPLICATES NT2_${COMPONENT_U}_INCLUDE_DIR)
    endif()
    set(NT2_${COMPONENT_U}_LIBRARY_DIR ${NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARY_DIR})
    set(NT2_${COMPONENT_U}_LIBRARIES ${NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARIES} ${NT2_${COMPONENT_U}_LIBRARIES})
    if(NT2_${COMPONENT_U}_LIBRARIES)
      list(REMOVE_DUPLICATES NT2_${COMPONENT_U}_LIBRARIES)
    endif()
    
    if(NOT NT2_${COMPONENT_U}_FOUND)
      nt2_find_log("${COMPONENT} dependencies not met")
    endif()
    
    #message(STATUS "[FindNT2] Variables for module ${COMPONENT}")
    #message(STATUS "[FindNT2] -- NT2_${COMPONENT_U}_FOUND = ${NT2_${COMPONENT_U}_FOUND}")
    #message(STATUS "[FindNT2] -- NT2_${COMPONENT_U}_INCLUDE_DIR = ${NT2_${COMPONENT_U}_INCLUDE_DIR}")
    #message(STATUS "[FindNT2] -- NT2_${COMPONENT_U}_LIBRARY_DIR = ${NT2_${COMPONENT_U}_LIBRARY_DIR}")
    #message(STATUS "[FindNT2] -- NT2_${COMPONENT_U}_LIBRARIES = ${NT2_${COMPONENT_U}_LIBRARIES}")
    
  endif()
    
    nt2_copy_parent( NT2_${COMPONENT_U}_FOUND
                     NT2_${COMPONENT_U}_INCLUDE_DIR NT2_${COMPONENT_U}_LIBRARY_DIR
                     NT2_${COMPONENT_U}_LIBRARIES
                   )
                   
    set(NT2_${COMPONENT_U}_FOUND_COMPONENTS ${NT2_FOUND_COMPONENTS} PARENT_SCOPE)
  
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
                     NT2_${COMPONENT_U_}_LIBRARIES
                   )
  endforeach()
endmacro()

function(nt2_find_top)

  set(NT2_FOUND 1)
  set(NT2_INCLUDE_DIR "")
  set(NT2_LIBRARY_DIR "")
  set(NT2_LIBRARIES "")
  set(NT2_FOUND_COMPONENTS "")
  
  if(DEFINED NT2_FIND_RECURSIVE)
    set(NT2_FIND_RECURSIVE_ "${NT2_FIND_RECURSIVE_}  ")
    set(NT2_FIND_RECURSIVE "${NT2_FIND_RECURSIVE_} \\_ ")
  else()
    set(NT2_FIND_RECURSIVE " ")
  endif()
  if(NOT DEFINED NT2_CURRENT_MODULE)
      set(NT2_CURRENT_MODULE " ")
  endif()

  if(NOT DEFINED NT2_MODULAR_ROOT AND DEFINED ENV{NT2_MODULAR_ROOT})
    nt2_find_log("found modular root")
    set(NT2_MODULAR_ROOT $ENV{NT2_MODULAR_ROOT})
  endif()

  foreach(COMPONENT ${ARGV})
    string(TOUPPER ${COMPONENT} COMPONENT_U)
    nt2_find(${COMPONENT})
    if(NT2_FOUND AND NT2_${COMPONENT_U}_FOUND)
        set(NT2_FOUND 1)
        set(NT2_FOUND_COMPONENTS ${COMPONENT} ${NT2_FOUND_COMPONENTS})
    else()
        set(NT2_FOUND 0)
    endif()
    nt2_prepend_module(INCLUDE_DIR)
    nt2_prepend_module(LIBRARY_DIR)
    nt2_prepend_module(LIBRARIES)
    nt2_prepend_module(FOUND_COMPONENTS)
    nt2_flag_found()
  endforeach()
  
  nt2_copy_parent( NT2_FOUND
                   NT2_INCLUDE_DIR NT2_LIBRARY_DIR
                   NT2_LIBRARIES
                   NT2_FOUND_COMPONENTS
                 )

endfunction()

nt2_find_top(${NT2_FIND_COMPONENTS})
if(NT2_FIND_RECURSIVE)
  nt2_flag_found()
endif()
