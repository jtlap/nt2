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
# It defines the following variables, with COMPONENT_U being a module set to uppercase:
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
# - NT2_FOUND_COMPONENTS            list of all NT2 modules that have been found
# - NT2_MODULE_PATH                 list of directories containing NT2 CMake modules
#
# Additionally, the script also adds all the NT2-specific CMake modules to the CMAKE_MODULE_PATH.
#
# You can set the following variables to help the script:
# - NT2_ROOT                        root of the NT2 installation or "share" directory
# - NT2_INCLUDE_ROOT                root of the includes of a NT2 installation (defaults to NT2_ROOT/include)
# - NT2_LIBRARY_ROOT                root of the libraries of a NT2 installation (defaults to NT2_ROOT/lib)
# - NT2_SOURCE_ROOT                 root of the NT2 source 
# - NT2_CURRENT_MODULE              current module being compiled, can be used to avoid self-dependencies
#                                   when compiling a NT2 module
#
# a NT2 module with its name in uppercase as ${COMPONENT_U} may set the following variables in its dependencies file:
# - NT2_${COMPONENT_U}_DEPENDENCIES_FOUND          whether all dependencies were found
# - NT2_${COMPONENT_U}_DEPENDENCIES_INCLUDE_DIR    include directories of all dependencies
# - NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARY_DIR    library directories of all dependencies
# - NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARIES      libraries that the module depends on
# - NT2_${COMPONENT_U}_DEPENDENCIES_FLAGS          flags required for the dependencies of the module
# - NT2_${COMPONENT_U}_DEPENDENCIES_EXTRA          extra NT2 modules the module is interdependent with. Does not guarantee
#                                                  order in which modules are loaded, so not suitable for overriding.
# - NT2_${COMPONENT_U}_LIBRARIES                   libraries provided by the module
# - NT2_${COMPONENT_U}_FLAGS                       flags required to use the module

include(NT2Module)

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

function(nt2_find_info)
  message(WARNING "[FindNT2]${NT2_FIND_RECURSIVE}${ARGV}")
endfunction()

macro(nt2_remove_duplicates)
  foreach(ARG ${ARGV})
    if(${ARG})
      list(REMOVE_DUPLICATES ${ARG})
    endif()
  endforeach()
endmacro()

macro(nt2_str_remove_duplicates)
  foreach(str ${ARGV})
    if(NOT ${str})
      set(${str} " ")
    endif()
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

macro(nt2_lib_remove_duplicates list)
  set(list2)
  set(qualifier)
  foreach(elem ${${list}})
    if(elem STREQUAL "debug"
    OR elem STREQUAL "optimized"
    OR elem STREQUAL "general"
      )
      set(qualifier ${elem})
    else()
      list(FIND list2 ${elem} FOUND)
      if(FOUND EQUAL -1)
        list(APPEND list2 ${qualifier} ${elem})
        set(qualifier)
      endif()
    endif()
  endforeach()
  set(${list} ${list2})
endmacro()

macro(nt2_find_module_path_push)
  set(CMAKE_MODULE_PATH_ ${CMAKE_MODULE_PATH})
  set(CMAKE_MODULE_PATH ${NT2_MODULE_PATH} ${CMAKE_MODULE_PATH})
endmacro()

macro(nt2_find_module_path_pop)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH_})
endmacro()

macro(nt2_find_module_dependencies _COMPONENT)

  string(TOUPPER ${_COMPONENT} _COMPONENT_U)
  
  if(NT2_MODULES_BLACKLIST)
    list(FIND NT2_MODULES_BLACKLIST ${_COMPONENT} _COMPONENT_INDEX)
    if(NOT _COMPONENT_INDEX EQUAL -1)
      nt2_find_log("${_COMPONENT} is blacklisted, skipping")
      return()
    endif()
  endif()
  
  string(REPLACE "." "/" _COMPONENT_PATH ${_COMPONENT})
  # Search for module source
  if(NOT NT2_${_COMPONENT_U}_ROOT)
    find_file( NT2_${_COMPONENT_U}_ROOT ${_COMPONENT_PATH}
               PATHS ${NT2_SOURCE_ROOT}/modules
               ENV NT2_${_COMPONENT_U}_ROOT
               DOC "Root directory of the ${_COMPONENT} module's source"
               NO_DEFAULT_PATH
             )
    mark_as_advanced(NT2_${_COMPONENT_U}_ROOT)
  endif()
  if(NT2_${COMPONENT_U}_ROOT AND NOT EXISTS "${NT2_${COMPONENT_U}_ROOT}/CMakeLists.txt")
    nt2_find_info("root of module ${COMPONENT} invalid: ${NT2_${COMPONENT_U}_ROOT}")
  endif()
    
  # Source found
  if(NT2_${_COMPONENT_U}_ROOT)
  
    nt2_find_log("${_COMPONENT} source found, testing dependencies")
    set(NT2_MODULE_PATH "${NT2_${_COMPONENT_U}_ROOT}/cmake" ${NT2_MODULE_PATH} CACHE STRING "List of directories in which to search for NT2 CMake includes" FORCE)
    mark_as_advanced(NT2_MODULE_PATH)
    
    set(NT2_${_COMPONENT_U}_INCLUDE_ROOT ${NT2_BINARY_DIR}/include ${NT2_${_COMPONENT_U}_ROOT}/include)
    set(NT2_${_COMPONENT_U}_LIBRARY_ROOT ${NT2_BINARY_DIR}/lib)
  
  # Look for module in install
  elseif(NT2_ROOT)
    if(NOT EXISTS ${NT2_ROOT}/modules/${_COMPONENT}.manifest)
      nt2_find_log("${_COMPONENT} not found in nt2 install")
      return()
    endif()
    
    nt2_find_log("${_COMPONENT} install found, testing dependencies")
    
    set(NT2_${_COMPONENT_U}_INCLUDE_ROOT ${NT2_INCLUDE_ROOT})
    set(NT2_${_COMPONENT_U}_LIBRARY_ROOT ${NT2_LIBRARY_ROOT})
  endif()
  
  # Try to download source if not available
  if(NOT NT2_${_COMPONENT_U}_ROOT AND NOT NT2_ROOT)
    nt2_find_module_path_push()
    include(nt2.download OPTIONAL RESULT_VARIABLE NT2_DOWNLOAD_CMAKE)
    nt2_find_module_path_pop()
    if(NT2_DOWNLOAD_CMAKE AND NOT NT2_${_COMPONENT_U}_ROOT)
      nt2_download_module(${_COMPONENT})
    endif()
  
    # Source download found
    if(NT2_${_COMPONENT_U}_ROOT)
  
      nt2_find_log("${_COMPONENT} source found, testing dependencies")
      set(NT2_MODULE_PATH "${NT2_${_COMPONENT_U}_ROOT}/cmake" ${NT2_MODULE_PATH} CACHE STRING "List of directories in which to search for NT2 CMake includes" FORCE)
      mark_as_advanced(NT2_MODULE_PATH)
    
      set(NT2_${_COMPONENT_U}_INCLUDE_ROOT ${NT2_BINARY_DIR}/include ${NT2_${_COMPONENT_U}_ROOT}/include)
      set(NT2_${_COMPONENT_U}_LIBRARY_ROOT ${NT2_BINARY_DIR}/lib)
    endif()
  endif()
  
  # No source nor install
  if(NOT NT2_${_COMPONENT_U}_ROOT AND NOT NT2_ROOT)
    nt2_find_log("can't find ${_COMPONENT} in source nor install")
    return()
  endif()

  unset(NT2_${_COMPONENT_U}_FOUND)
  unset(NT2_${_COMPONENT_U}_INCLUDE_DIR CACHE)
  unset(NT2_${_COMPONENT_U}_LIBRARY_DIR CACHE)
  unset(NT2_${_COMPONENT_U}_LIBRARIES CACHE)
  unset(NT2_${_COMPONENT_U}_FLAGS CACHE)

  nt2_find_module_path_push()
  include("nt2.${_COMPONENT}.dependencies" OPTIONAL)
  nt2_find_module_path_pop()
    
  if(NOT DEFINED NT2_${_COMPONENT_U}_DEPENDENCIES_FOUND)
    set(NT2_${_COMPONENT_U}_DEPENDENCIES_FOUND 1)
  endif()
  
endmacro()

macro(nt2_append_if lst)
  foreach(ARG ${ARGN})
    if(${ARG})
        set(${lst} ${${lst}} ${${ARG}})
    endif()
  endforeach()
endmacro()

function(nt2_find_module COMPONENT)

  string(TOUPPER ${COMPONENT} COMPONENT_U)

  # Load dependencies of current and all extra modules
  set(NT2_${COMPONENT_U}_DEPENDENCIES_FOUND 1)
  set(NT2_${COMPONENT_U}_EXTRA_REST ${COMPONENT})
  set(NT2_${COMPONENT_U}_EXTRA)
  while(NT2_${COMPONENT_U}_DEPENDENCIES_FOUND AND NT2_${COMPONENT_U}_EXTRA_REST)
    list(GET NT2_${COMPONENT_U}_EXTRA_REST 0 EXTRA_COMPONENT)
    string(TOUPPER ${EXTRA_COMPONENT} EXTRA_COMPONENT_U)

    get_property(NT2_${EXTRA_COMPONENT_U}_FOUND GLOBAL PROPERTY NT2_${EXTRA_COMPONENT_U}_FOUND)
    if(NT2_${EXTRA_COMPONENT_U}_FOUND)
      nt2_find_log("${EXTRA_COMPONENT} already found")
      
      nt2_append_if(NT2_${COMPONENT_U}_DEPENDENCIES_INCLUDE_DIR NT2_${EXTRA_COMPONENT_U}_INCLUDE_DIR)
      nt2_append_if(NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARY_DIR NT2_${EXTRA_COMPONENT_U}_LIBRARY_DIR)
      nt2_append_if(NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARIES NT2_${EXTRA_COMPONENT_U}_LIBRARIES)
      set(NT2_${COMPONENT_U}_DEPENDENCIES_FLAGS "${NT2_${COMPONENT_U}_DEPENDENCIES_FLAGS} ${NT2_${EXTRA_COMPONENT_U}_FLAGS}")
      
    else()
      nt2_find_log("loading dependencies of ${EXTRA_COMPONENT}")
      nt2_find_module_dependencies(${EXTRA_COMPONENT})
    
      if(NOT NT2_${EXTRA_COMPONENT_U}_DEPENDENCIES_FOUND)
        set(NT2_${COMPONENT_U}_DEPENDENCIES_FOUND 0)
      else()
      
        if(NOT EXTRA_COMPONENT STREQUAL ${COMPONENT})
          nt2_append_if(NT2_${COMPONENT_U}_DEPENDENCIES_INCLUDE_DIR NT2_${EXTRA_COMPONENT_U}_INCLUDE_ROOT)
          nt2_append_if(NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARY_DIR NT2_${EXTRA_COMPONENT_U}_LIBRARY_ROOT)
        endif()
      
        nt2_append_if(NT2_${COMPONENT_U}_DEPENDENCIES_INCLUDE_DIR NT2_${EXTRA_COMPONENT_U}_DEPENDENCIES_INCLUDE_DIR)
        nt2_append_if(NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARY_DIR NT2_${EXTRA_COMPONENT_U}_DEPENDENCIES_LIBRARY_DIR)
        nt2_append_if(NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARIES NT2_${EXTRA_COMPONENT_U}_DEPENDENCIES_LIBRARIES)
        
        if(NOT EXTRA_COMPONENT STREQUAL ${COMPONENT})
          if(DEFINED NT2_${EXTRA_COMPONENT_U}_LIBRARIES)
            foreach(lib ${NT2_${EXTRA_COMPONENT_U}_LIBRARIES})
              list(APPEND NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARIES optimized ${lib} debug ${lib}_d)
            endforeach()
          endif()
          #nt2_append_if(NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARIES NT2_${EXTRA_COMPONENT_U}_LIBRARIES)
        endif()
        
        set(NT2_${COMPONENT_U}_DEPENDENCIES_FLAGS "${NT2_${COMPONENT_U}_DEPENDENCIES_FLAGS} ${NT2_${EXTRA_COMPONENT_U}_DEPENDENCIES_FLAGS}")
        if(NOT EXTRA_COMPONENT STREQUAL ${COMPONENT})
          set(NT2_${COMPONENT_U}_DEPENDENCIES_FLAGS "${NT2_${COMPONENT_U}_DEPENDENCIES_FLAGS} ${NT2_${EXTRA_COMPONENT_U}_FLAGS}")
        endif()
        
      endif()
    endif()
    
    nt2_remove_duplicates( NT2_${COMPONENT_U}_DEPENDENCIES_INCLUDE_DIR NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARY_DIR )
    nt2_lib_remove_duplicates( NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARIES )
    nt2_str_remove_duplicates( NT2_${COMPONENT_U}_DEPENDENCIES_FLAGS )
    
    nt2_append_if(NT2_${COMPONENT_U}_EXTRA EXTRA_COMPONENT)
    list(REMOVE_DUPLICATES NT2_${COMPONENT_U}_EXTRA)
    
    nt2_append_if(NT2_${COMPONENT_U}_EXTRA_REST NT2_${EXTRA_COMPONENT_U}_DEPENDENCIES_EXTRA)
    list(REMOVE_DUPLICATES NT2_${COMPONENT_U}_EXTRA_REST)
    list(REMOVE_ITEM NT2_${COMPONENT_U}_EXTRA_REST ${NT2_${COMPONENT_U}_EXTRA})
    
  endwhile()

  if(NOT NT2_${COMPONENT_U}_DEPENDENCIES_FOUND)
    nt2_find_log("${COMPONENT} dependencies not met")
    return()
  endif()
  
  nt2_find_log("${COMPONENT} dependencies met")
  
  set(NT2_${COMPONENT_U}_INCLUDE_DIR ${NT2_${COMPONENT_U}_DEPENDENCIES_INCLUDE_DIR} ${NT2_${COMPONENT_U}_INCLUDE_ROOT})
  set(NT2_${COMPONENT_U}_LIBRARY_DIR ${NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARY_DIR} ${NT2_${COMPONENT_U}_LIBRARY_ROOT})
  nt2_append_if(NT2_${COMPONENT_U}_LIBRARIES NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARIES)
  set(NT2_${COMPONENT_U}_FLAGS "${NT2_${COMPONENT_U}_DEPENDENCIES_FLAGS} ${NT2_${COMPONENT_U}_FLAGS}")
  
  nt2_remove_duplicates( NT2_${COMPONENT_U}_INCLUDE_DIR NT2_${COMPONENT_U}_LIBRARY_DIR )
  nt2_lib_remove_duplicates( NT2_${COMPONENT_U}_LIBRARIES )
  nt2_str_remove_duplicates( NT2_${COMPONENT_U}_FLAGS )
  
  foreach(EXTRA_COMPONENT ${NT2_${COMPONENT_U}_EXTRA})
    string(TOUPPER ${EXTRA_COMPONENT} EXTRA_COMPONENT_U)
    
    get_property(NT2_${EXTRA_COMPONENT_U}_FOUND GLOBAL PROPERTY NT2_${EXTRA_COMPONENT_U}_FOUND)
    if(NOT NT2_${EXTRA_COMPONENT_U}_FOUND)

      define_property(GLOBAL PROPERTY NT2_${EXTRA_COMPONENT_U}_FOUND
                      BRIEF_DOCS "Whether NT2 module ${EXTRA_COMPONENT} was found"
                      FULL_DOCS "Global flag to avoid building NT2 module ${EXTRA_COMPONENT} multiple times"
                     )
      set_property(GLOBAL PROPERTY NT2_${EXTRA_COMPONENT_U}_FOUND 1)

      # Set variables
      set(NT2_${EXTRA_COMPONENT_U}_FOUND 1)
      set(NT2_${EXTRA_COMPONENT_U}_INCLUDE_DIR ${NT2_${COMPONENT_U}_INCLUDE_DIR} CACHE INTERNAL "Include directories for NT2 module ${EXTRA_COMPONENT}" FORCE)
      set(NT2_${EXTRA_COMPONENT_U}_LIBRARY_DIR ${NT2_${COMPONENT_U}_LIBRARY_DIR} CACHE INTERNAL "Library directories for NT2 module ${EXTRA_COMPONENT}" FORCE)
      set(NT2_${EXTRA_COMPONENT_U}_LIBRARIES ${NT2_${COMPONENT_U}_LIBRARIES} CACHE INTERNAL "Libraries for NT2 module ${EXTRA_COMPONENT}" FORCE)
      set(NT2_${EXTRA_COMPONENT_U}_FLAGS ${NT2_${COMPONENT_U}_FLAGS} CACHE INTERNAL "Compilation flags for NT2 module ${EXTRA_COMPONENT}" FORCE)
    
      mark_as_advanced(NT2_${EXTRA_COMPONENT_U}_FOUND
                       NT2_${EXTRA_COMPONENT_U}_INCLUDE_DIR NT2_${EXTRA_COMPONENT_U}_LIBRARY_DIR
                       NT2_${EXTRA_COMPONENT_U}_LIBRARIES NT2_${EXTRA_COMPONENT_U}_FLAGS
                      )
    
      # Debug info
      nt2_find_log("${EXTRA_COMPONENT} variables:")
      nt2_find_log(" - NT2_${EXTRA_COMPONENT_U}_FOUND = ${NT2_${EXTRA_COMPONENT_U}_FOUND}")
      nt2_find_log(" - NT2_${EXTRA_COMPONENT_U}_INCLUDE_DIR = ${NT2_${EXTRA_COMPONENT_U}_INCLUDE_DIR}")
      nt2_find_log(" - NT2_${EXTRA_COMPONENT_U}_LIBRARY_DIR = ${NT2_${EXTRA_COMPONENT_U}_LIBRARY_DIR}")
      nt2_find_log(" - NT2_${EXTRA_COMPONENT_U}_LIBRARIES = ${NT2_${EXTRA_COMPONENT_U}_LIBRARIES}")
      nt2_find_log(" - NT2_${EXTRA_COMPONENT_U}_FLAGS = ${NT2_${EXTRA_COMPONENT_U}_FLAGS}")
    
      # Configure/build if source
      if(NT2_${EXTRA_COMPONENT_U}_ROOT)
        nt2_find_module_path_push()
        if(IS_DIRECTORY ${NT2_${EXTRA_COMPONENT_U}_ROOT}/src)
          add_subdirectory(${NT2_${EXTRA_COMPONENT_U}_ROOT}/src ${NT2_BINARY_DIR}/modules/${EXTRA_COMPONENT}/src)
        else()
          file(MAKE_DIRECTORY ${NT2_BINARY_DIR}/modules/${EXTRA_COMPONENT}/src)
          file(WRITE ${NT2_BINARY_DIR}/modules/${EXTRA_COMPONENT}/src/CMakeLists.txt "include(NT2Module)\nnt2_module_source_setup(${EXTRA_COMPONENT})")
          add_subdirectory(${NT2_BINARY_DIR}/modules/${EXTRA_COMPONENT}/src ${NT2_BINARY_DIR}/modules/${EXTRA_COMPONENT}/src)
        endif()
        nt2_find_module_path_pop()
      endif()
    endif()
    
    nt2_copy_parent(NT2_${EXTRA_COMPONENT_U}_FOUND)

  endforeach()
  
  # Copy over to parent
  nt2_append_if(NT2_FOUND_COMPONENTS NT2_${COMPONENT_U}_EXTRA)
  nt2_remove_duplicates(NT2_FOUND_COMPONENTS)
  set(NT2_FOUND_COMPONENTS ${NT2_FOUND_COMPONENTS} CACHE INTERNAL "")
    
endfunction()

macro(nt2_prepend_module name)
  set(NT2_${name} ${NT2_${COMPONENT_U}_${name}} ${NT2_${name}})
  if(NT2_${name})
    list(REMOVE_DUPLICATES NT2_${name})
  endif()
endmacro()

function(nt2_find)

  set(NT2_FOUND 1)
  set(NT2_INCLUDE_DIR "")
  set(NT2_LIBRARY_DIR "")
  set(NT2_LIBRARIES "")
  set(NT2_FLAGS " ")
  
  if(NOT DEFINED NT2_BINARY_DIR)
    set(NT2_BINARY_DIR ${PROJECT_BINARY_DIR}/nt2)
  endif()
  
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
    find_path ( NT2_ROOT modules
                PATHS /Applications/NT2
                      /usr/local/share/nt2 /usr/share/nt2 /opt/nt2
                      "C:\\Program Files\\NT2"
                ENV NT2_ROOT
                DOC "Root directory in which NT2 is installed"
                NO_DEFAULT_PATH
              )
    mark_as_advanced(NT2_ROOT)
    if(NT2_ROOT)
      nt2_find_log("found NT2 root ${NT2_ROOT}")
    endif()
  endif()

  # Search for include and library directories, which may be stored separately from
  # NT2_ROOT on some platforms
  if(NT2_ROOT)

    if(NOT NT2_INCLUDE_ROOT)
      find_path ( NT2_INCLUDE_ROOT nt2
                  PATHS ${NT2_ROOT}/include
                        /usr/local/include /usr/include
                  ENV NT2_INCLUDE_ROOT
                  DOC "Root directory in which the NT2 headers are installed"
                  NO_DEFAULT_PATH
                )
      mark_as_advanced(NT2_INCLUDE_ROOT)
      if(NOT NT2_INCLUDE_ROOT)
        nt2_find_info("could find install but not include root, bad install?")
      else()
        nt2_find_log("found NT2 include root ${NT2_INCLUDE_ROOT}")
      endif()
    endif()
    
    if(NOT NT2_LIBRARY_ROOT)
      find_file ( NT2_LIBRARY_ROOT ${CMAKE_STATIC_LIBRARY_PREFIX}nt2${CMAKE_STATIC_LIBRARY_SUFFIX}
                  PATHS ${NT2_ROOT}/lib
                        /usr/local/lib /usr/lib
                  ENV NT2_LIBRARY_ROOT
                  DOC "Root directory in which the NT2 libraries are installed"
                  NO_DEFAULT_PATH
                )
      mark_as_advanced(NT2_LIBRARY_ROOT)
      if(NOT NT2_LIBRARY_ROOT)
        nt2_find_info("could find install but not library root, bad install?")
      else()
        nt2_find_log("found NT2 library root ${NT2_LIBRARY_ROOT}")
      endif()
    endif()
    
  endif()

  # Add install and source cmake directories to module path if they're not
  # already there, prefer source over install
  if(NT2_ROOT AND NOT NT2_ROOT_IN_MODULE_PATH)
    set(NT2_MODULE_PATH ${NT2_ROOT}/cmake ${NT2_MODULE_PATH} CACHE STRING "List of directories in which to search for NT2 CMake includes" FORCE)
    mark_as_advanced(NT2_MODULE_PATH)
    set(NT2_ROOT_IN_MODULE_PATH 1 CACHE INTERNAL "")
  endif()

  if(NT2_SOURCE_ROOT AND NOT NT2_SOURCE_ROOT_IN_MODULE_PATH)
    set(NT2_MODULE_PATH ${NT2_SOURCE_ROOT}/cmake ${NT2_MODULE_PATH} CACHE STRING "List of directories in which to search for NT2 CMake includes" FORCE)
    mark_as_advanced(NT2_MODULE_PATH)
    set(NT2_SOURCE_ROOT_IN_MODULE_PATH 1 CACHE INTERNAL "")
  endif()
  
  # if no component specified, we glob the source or install directories for modules
  if(ARGC EQUAL 0)
    if(NT2_SOURCE_ROOT)
      file(GLOB NT2_COMPONENTS RELATIVE ${NT2_SOURCE_ROOT}/modules ${NT2_SOURCE_ROOT}/modules/*/)
      set(i 0)
      list(LENGTH NT2_COMPONENTS len)
      while(i LESS len)
        list(GET NT2_COMPONENTS ${i} module)
        string(REPLACE "." "/" module_path ${module})
        if(${module} MATCHES boostification)
          list(REMOVE_ITEM NT2_COMPONENTS ${module})
          list(LENGTH NT2_COMPONENTS len)
        elseif(NOT EXISTS ${NT2_SOURCE_ROOT}/modules/${module_path}/CMakeLists.txt)
          list(REMOVE_ITEM NT2_COMPONENTS ${module})
          file(GLOB NT2_COMPONENTS_ RELATIVE ${NT2_SOURCE_ROOT}/modules ${NT2_SOURCE_ROOT}/modules/${module_path}/*/)
          if(NT2_COMPONENTS_)
            string(REPLACE "/" "." NT2_COMPONENTS_ "${NT2_COMPONENTS_}")
            list(APPEND NT2_COMPONENTS ${NT2_COMPONENTS_})
          endif()
          list(LENGTH NT2_COMPONENTS len)
        else()
          math(EXPR i "${i} + 1")
        endif()
      endwhile()
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
      set(ARGV ${NT2_COMPONENTS})
    endif()
  endif()
  
  get_property(NT2_POSTCONFIGURE_INITED GLOBAL PROPERTY NT2_POSTCONFIGURE_INITED)
  if(NOT NT2_POSTCONFIGURE_INITED AND NT2_SOURCE_ROOT)
    nt2_postconfigure_init()
  endif()

  # Search for all requested components
  foreach(COMPONENT ${ARGV})
    string(TOUPPER ${COMPONENT} COMPONENT_U)
    nt2_find_module(${COMPONENT})
    if(NT2_${COMPONENT_U}_FOUND)
      nt2_prepend_module(INCLUDE_DIR)
      nt2_prepend_module(LIBRARY_DIR)
    
      set(NT2_LIBRARIES ${NT2_${COMPONENT_U}_LIBRARIES} ${NT2_LIBRARIES})
      nt2_lib_remove_duplicates(NT2_LIBRARIES)
    
      set(NT2_FLAGS "${NT2_${COMPONENT_U}_FLAGS} ${NT2_FLAGS}")
      nt2_str_remove_duplicates(NT2_FLAGS)
    elseif(NT2_FIND_COMPONENTS)
      set(NT2_FOUND 0)
    endif()
    
    nt2_copy_parent(NT2_${COMPONENT_U}_FOUND)
  endforeach()
  
  nt2_copy_parent( NT2_FOUND
                   NT2_INCLUDE_DIR NT2_LIBRARY_DIR
                   NT2_LIBRARIES NT2_FLAGS
                 )
                 
  if(NOT NT2_POSTCONFIGURE_INITED AND NT2_SOURCE_ROOT)
    nt2_postconfigure_run()
  endif()
  
  if(NT2_FIND_REQUIRED AND NOT NT2_FOUND)
    message(FATAL_ERROR "NT2 was not found")
  endif()

endfunction()

nt2_find(${NT2_FIND_COMPONENTS})
