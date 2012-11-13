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
# - NT2_${COMPONENT_U}_COMPILE_FLAGS flags that must be passed to the compiler to use the component
# - NT2_${COMPONENT_U}_LINK_FLAGS   flags that must be passed to the linker to use the component
# - NT2_COMPILE_FLAGS               flags that must be passed to the compiler to use all the requested components
# - NT2_LINK_FLAGS                  flags that must be passed to the linker to use all the requested components
# - NT2_FOUND_COMPONENTS            list of all NT2 modules that have been found
# - NT2_MODULE_PATH                 list of directories containing NT2 CMake modules
# - NT2_USE_FILE                    file to include to use everything that has been found
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
# - NT2_${COMPONENT_U}_DEPENDENCIES_COMPILE_FLAGS  compile flags required for the dependencies of the module
# - NT2_${COMPONENT_U}_DEPENDENCIES_LINK_FLAGS     link flags required for the dependencies of the module
# - NT2_${COMPONENT_U}_DEPENDENCIES_EXTRA          extra NT2 modules the module is interdependent with. Does not guarantee
#                                                  order in which modules are loaded, so not suitable for overriding.
# - NT2_${COMPONENT_U}_LIBRARIES                   libraries provided by the module
# - NT2_${COMPONENT_U}_COMPILE_FLAGS               compile flags required to use the module
# - NT2_${COMPONENT_U}_LINK_FLAGS                  link flags required to use the module

include(NT2Module)
include(TopologicalSortU)

macro(nt2_copy_parent)
  foreach(ARG ${ARGV})
    set(${ARG} ${${ARG}} PARENT_SCOPE)
  endforeach()
endmacro()

function(nt2_find_log)
  if(NT2_FIND_VERBOSE OR ENV{NT2_FIND_VERBOSE})
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

# Find location of source or binary module:
# - Defines variables NT2_${_COMPONENT_U}_INCLUDE_ROOT and NT2_${_COMPONENT_U}_LIBRARY_ROOT
# - Potentially finds NT2_${COMPONENT_U}_ROOT if source module
# - Adds module CMake directory to NT2_MODULE_PATH
function(nt2_find_module_location _COMPONENT)

  string(TOUPPER ${_COMPONENT} _COMPONENT_U)

  foreach(bl ${NT2_MODULES_BLACKLIST})
    if(${_COMPONENT} MATCHES "^${bl}($|\\.)")
      nt2_find_log("${_COMPONENT} is blacklisted, skipping")
      return()
    endif()
  endforeach()

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
  if(NT2_${_COMPONENT_U}_ROOT AND NOT EXISTS "${NT2_${_COMPONENT_U}_ROOT}/CMakeLists.txt")
    nt2_find_info("root of module ${_COMPONENT} invalid: ${NT2_${_COMPONENT_U}_ROOT}")
  endif()

  # Source found
  if(NT2_${_COMPONENT_U}_ROOT)

    nt2_find_log("${_COMPONENT} source found, testing dependencies")
    list(FIND NT2_MODULE_PATH "${NT2_${_COMPONENT_U}_ROOT}/cmake" NT2_COMPONENT_IN_MODULE_PATH)
    if(NT2_COMPONENT_IN_MODULE_PATH EQUAL -1)
      set(NT2_MODULE_PATH "${NT2_${_COMPONENT_U}_ROOT}/cmake" ${NT2_MODULE_PATH} CACHE STRING "List of directories in which to search for NT2 CMake includes" FORCE)
      mark_as_advanced(NT2_MODULE_PATH)
    endif()

    set(NT2_${_COMPONENT_U}_INCLUDE_ROOT ${NT2_BINARY_INCLUDE_DIR} ${NT2_${_COMPONENT_U}_ROOT}/include PARENT_SCOPE)
    set(NT2_${_COMPONENT_U}_LIBRARY_ROOT ${NT2_BINARY_DIR}/lib PARENT_SCOPE)

  # Look for module in install
  elseif(NT2_ROOT)
    if(NOT EXISTS ${NT2_ROOT}/modules/${_COMPONENT}.manifest)
      nt2_find_log("${_COMPONENT} not found in nt2 install")
      return()
    endif()

    nt2_find_log("${_COMPONENT} install found, testing dependencies")

    set(NT2_${_COMPONENT_U}_INCLUDE_ROOT ${NT2_INCLUDE_ROOT} PARENT_SCOPE)
    set(NT2_${_COMPONENT_U}_LIBRARY_ROOT ${NT2_LIBRARY_ROOT} PARENT_SCOPE)
  endif()

  # Try to download source if not available
  if(NOT NT2_${_COMPONENT_U}_ROOT AND NOT NT2_ROOT)
    if(NOT NT2_DOWNLOAD_CMAKE)
      nt2_find_module_path_push()
      include(nt2.download OPTIONAL RESULT_VARIABLE NT2_DOWNLOAD_CMAKE)
      nt2_find_module_path_pop()
    endif()
    if(NT2_DOWNLOAD_CMAKE AND NOT NT2_${_COMPONENT_U}_ROOT)
      nt2_download_module(${_COMPONENT})
    endif()

    # Source download found
    if(NT2_${_COMPONENT_U}_ROOT)

      nt2_find_log("${_COMPONENT} source found, testing dependencies")
      list(FIND NT2_MODULE_PATH "${NT2_${_COMPONENT_U}_ROOT}/cmake" NT2_COMPONENT_IN_MODULE_PATH)
      if(NT2_COMPONENT_IN_MODULE_PATH EQUAL -1)
        set(NT2_MODULE_PATH "${NT2_${_COMPONENT_U}_ROOT}/cmake" ${NT2_MODULE_PATH} CACHE STRING "List of directories in which to search for NT2 CMake includes" FORCE)
        mark_as_advanced(NT2_MODULE_PATH)
      endif()

      set(NT2_${_COMPONENT_U}_INCLUDE_ROOT ${NT2_BINARY_INCLUDE_DIR} ${NT2_${_COMPONENT_U}_ROOT}/include PARENT_SCOPE)
      set(NT2_${_COMPONENT_U}_LIBRARY_ROOT ${NT2_BINARY_DIR}/lib PARENT_SCOPE)
    endif()
  endif()

  # No source nor install
  if(NOT NT2_${_COMPONENT_U}_ROOT AND NOT NT2_ROOT)
    nt2_find_log("can't find ${_COMPONENT} in source nor install")
  endif()

endfunction()

# includes the dependencies file
# must be a macro to keep all variables in scope
macro(nt2_find_module_dependencies _COMPONENT)

  string(TOUPPER ${_COMPONENT} _COMPONENT_U)

  nt2_find_module_location(${_COMPONENT})

  unset(NT2_${_COMPONENT_U}_FOUND)
  unset(NT2_${_COMPONENT_U}_INCLUDE_DIR CACHE)
  unset(NT2_${_COMPONENT_U}_LIBRARY_DIR CACHE)
  unset(NT2_${_COMPONENT_U}_LIBRARIES CACHE)
  unset(NT2_${_COMPONENT_U}_COMPILE_FLAGS CACHE)
  unset(NT2_${_COMPONENT_U}_LINK_FLAGS CACHE)

  if(NT2_${COMPONENT_U}_INCLUDE_ROOT)
    nt2_find_module_path_push()
    include("nt2.${_COMPONENT}.dependencies" OPTIONAL)
    nt2_find_module_path_pop()
  else()
    set(NT2_${_COMPONENT_U}_DEPENDENCIES_FOUND 0)
  endif()

  if(NOT DEFINED NT2_${_COMPONENT_U}_DEPENDENCIES_FOUND)
    set(NT2_${_COMPONENT_U}_DEPENDENCIES_FOUND 1)
  endif()

endmacro()

# little helper for nt2_find_modules
macro(nt2_prepend_module name)
  set(NT2_${name} ${NT2_${COMPONENT_U}_${name}} ${NT2_${name}})
  if(NT2_${name})
    list(REMOVE_DUPLICATES NT2_${name})
  endif()
endmacro()

# sort modules to find topologically, find them all and
# aggregate results
function(nt2_find_modules)

  nt2_find_log("nt2_find_modules ${ARGN}")

  # load dependencies for all required components
  # build queue of all indirect dependencies
  set(EXTRA_REST ${ARGN})
  set(EXTRA)
  while(EXTRA_REST)
    list(GET EXTRA_REST 0 COMPONENT)
    string(TOUPPER ${COMPONENT} COMPONENT_U)

    # only load dependencies if not already found
    get_property(NT2_${COMPONENT_U}_FOUND GLOBAL PROPERTY NT2_${COMPONENT_U}_FOUND)
    if(NOT NT2_${COMPONENT_U}_FOUND)
      nt2_find_module_dependencies(${COMPONENT})
    endif()

    # remove current module from queue, add to list of processed modules
    # if dependencies found, add all extra modules to queue
    list(APPEND EXTRA ${COMPONENT})
    list(REMOVE_ITEM EXTRA_REST ${COMPONENT})
    if(NT2_${COMPONENT_U}_DEPENDENCIES_FOUND)
      foreach(extra ${NT2_${COMPONENT_U}_DEPENDENCIES_EXTRA})
        list(FIND EXTRA ${extra} extra_found)
        if(extra_found EQUAL -1)
          list(APPEND EXTRA_REST ${extra})
        endif()
      endforeach()
    endif()
  endwhile()

  # sorting in reverse topological order makes sure that dependencies
  # will get loaded before modules that depend on them
  topological_sort_u(EXTRA "NT2_" "_DEPENDENCIES_EXTRA")

  # load each module, aggregate results
  set(FOUND_COMPONENTS)
  foreach(COMPONENT ${EXTRA})
    string(TOUPPER ${COMPONENT} COMPONENT_U)
    nt2_find_module(${COMPONENT})
    if(NT2_${COMPONENT_U}_FOUND)
      list(APPEND FOUND_COMPONENTS ${COMPONENT})
      nt2_prepend_module(INCLUDE_DIR)
      nt2_prepend_module(LIBRARY_DIR)

      set(NT2_LIBRARIES ${NT2_${COMPONENT_U}_LIBRARIES} ${NT2_LIBRARIES})
      nt2_lib_remove_duplicates(NT2_LIBRARIES)

      set(NT2_COMPILE_FLAGS "${NT2_${COMPONENT_U}_COMPILE_FLAGS} ${NT2_COMPILE_FLAGS}")
      set(NT2_LINK_FLAGS "${NT2_${COMPONENT_U}_LINK_FLAGS} ${NT2_LINK_FLAGS}")
      nt2_str_remove_duplicates(NT2_COMPILE_FLAGS NT2_LINK_FLAGS)
    elseif(NT2_FIND_COMPONENTS)
      set(NT2_FOUND 0)
    endif()

    nt2_copy_parent(NT2_${COMPONENT_U}_FOUND)
  endforeach()

  set(NT2_FOUND_COMPONENTS ${NT2_FOUND_COMPONENTS} ${FOUND_COMPONENTS})
  nt2_remove_duplicates(NT2_FOUND_COMPONENTS)
  set(NT2_FOUND_COMPONENTS ${NT2_FOUND_COMPONENTS} CACHE INTERNAL "")

  nt2_copy_parent( NT2_FOUND
                   NT2_INCLUDE_DIR NT2_LIBRARY_DIR
                   NT2_LIBRARIES
                   NT2_COMPILE_FLAGS NT2_LINK_FLAGS
                   NT2_BINARY_DIR
                 )

endfunction()

# Gather all dependencies of a module, set them in global or cache variables.
# Also compile the source if source module.
function(nt2_find_module COMPONENT)
  string(TOUPPER ${COMPONENT} COMPONENT_U)

  get_property(NT2_${COMPONENT_U}_FOUND GLOBAL PROPERTY NT2_${COMPONENT_U}_FOUND)
  if(NT2_${COMPONENT_U}_FOUND)
    set(NT2_${COMPONENT_U}_FOUND 1 PARENT_SCOPE)
    return()
  endif()
  if(NOT NT2_${COMPONENT_U}_DEPENDENCIES_FOUND)
    set(NT2_${COMPONENT_U}_FOUND 0 PARENT_SCOPE)
    return()
  endif()

  # TODO: make sure the topological sort here is needed
  set(EXTRA ${NT2_${COMPONENT_U}_DEPENDENCIES_EXTRA})
  topological_sort_u(EXTRA "NT2_" "_DEPENDENCIES_EXTRA")

  set(CYCLIC)
  nt2_find_log("nt2_find_module ${COMPONENT}, dependencies: ${EXTRA}")

  # 'unroll' _DEPENDENCIES variables by adding content from extra
  foreach(extra ${EXTRA})
    string(TOUPPER ${extra} extra_U)

    get_property(NT2_${extra_U}_FOUND GLOBAL PROPERTY NT2_${extra_U}_FOUND)
    if(NOT NT2_${extra_U}_FOUND AND NOT ${extra} STREQUAL ${COMPONENT})
      nt2_find_log("nt2_find_module ${COMPONENT}, cycle with ${extra}")
      list(APPEND CYCLIC ${extra})
    endif()

    if(NT2_${extra_U}_FOUND)
      list(APPEND NT2_${COMPONENT_U}_DEPENDENCIES_INCLUDE_DIR ${NT2_${extra_U}_INCLUDE_DIR})
      list(APPEND NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARY_DIR ${NT2_${extra_U}_LIBRARY_DIR})
      list(APPEND NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARIES ${NT2_${extra_U}_LIBRARIES})

      set(NT2_${COMPONENT_U}_DEPENDENCIES_COMPILE_FLAGS "${NT2_${COMPONENT_U}_DEPENDENCIES_COMPILE_FLAGS} ${NT2_${extra_U}_COMPILE_FLAGS}")
      set(NT2_${COMPONENT_U}_DEPENDENCIES_LINK_FLAGS "${NT2_${COMPONENT_U}_DEPENDENCIES_LINK_FLAGS} ${NT2_${extra_U}_LINK_FLAGS}")
    endif()
  endforeach()

  # for cyclic dependencies, assume dependencies file just got loaded
  foreach(extra ${CYCLIC})
    string(TOUPPER ${extra} extra_U)

    list(APPEND NT2_${COMPONENT_U}_DEPENDENCIES_INCLUDE_DIR ${NT2_${extra_U}_DEPENDENCIES_INCLUDE_DIR} ${NT2_${extra_U}_INCLUDE_ROOT})
    list(APPEND NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARY_DIR ${NT2_${extra_U}_DEPENDENCIES_LIBRARY_DIR} ${NT2_${extra_U}_LIBRARY_ROOT})
    list(APPEND NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARIES ${NT2_${extra_U}_DEPENDENCIES_LIBRARIES} ${NT2_${extra_U}_LIBRARIES})
    set(NT2_${COMPONENT_U}_DEPENDENCIES_COMPILE_FLAGS "${NT2_${COMPONENT_U}_DEPENDENCIES_COMPILE_FLAGS} ${NT2_${extra_U}_DEPENDENCIES_COMPILE_FLAGS} ${NT2_${extra_U}_COMPILE_FLAGS}")
    set(NT2_${COMPONENT_U}_DEPENDENCIES_LINK_FLAGS "${NT2_${COMPONENT_U}_DEPENDENCIES_LINK_FLAGS} ${NT2_${extra_U}_DEPENDENCIES_LINK_FLAGS} ${NT2_${extra_U}_LINK_FLAGS}")
  endforeach()

  # Add self
  set(INCLUDE_DIR ${NT2_${COMPONENT_U}_DEPENDENCIES_INCLUDE_DIR} ${NT2_${COMPONENT_U}_INCLUDE_ROOT})
  set(LIBRARY_DIR ${NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARY_DIR} ${NT2_${COMPONENT_U}_LIBRARY_ROOT})
  set(LIBRARIES ${NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARIES} ${NT2_${COMPONENT_U}_LIBRARIES})
  set(COMPILE_FLAGS "${NT2_${COMPONENT_U}_DEPENDENCIES_COMPILE_FLAGS} ${NT2_${COMPONENT_U}_COMPILE_FLAGS}")
  set(LINK_FLAGS "${NT2_${COMPONENT_U}_DEPENDENCIES_LINK_FLAGS} ${NT2_${COMPONENT_U}_LINK_FLAGS}")

  nt2_remove_duplicates( INCLUDE_DIR LIBRARY_DIR NT2_${COMPONENT_U}_DEPENDENCIES_INCLUDE_DIR NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARY_DIR )
  nt2_lib_remove_duplicates( LIBRARIES NT2_${COMPONENT_U}_DEPENDENCIES_LIBRARIES )
  nt2_str_remove_duplicates( COMPILE_FLAGS LINK_FLAGS NT2_${COMPONENT_U}_DEPENDENCIES_COMPILE_FLAGS NT2_${COMPONENT_U}_DEPENDENCIES_LINK_FLAGS )

  # Set variables globally
  define_property(GLOBAL PROPERTY NT2_${COMPONENT_U}_FOUND
                  BRIEF_DOCS "Whether NT2 module ${COMPONENT} was found"
                  FULL_DOCS "Global flag to avoid building NT2 module ${COMPONENT} multiple times"
                 )
  set_property(GLOBAL PROPERTY NT2_${COMPONENT_U}_FOUND 1)

  set(NT2_${COMPONENT_U}_FOUND 1 PARENT_SCOPE)
  set(NT2_${COMPONENT_U}_INCLUDE_DIR ${INCLUDE_DIR} CACHE INTERNAL "Include directories for NT2 module ${COMPONENT}" FORCE)
  set(NT2_${COMPONENT_U}_LIBRARY_DIR ${LIBRARY_DIR} CACHE INTERNAL "Library directories for NT2 module ${COMPONENT}" FORCE)
  set(NT2_${COMPONENT_U}_LIBRARIES ${LIBRARIES} CACHE INTERNAL "Libraries for NT2 module ${COMPONENT}" FORCE)
  set(NT2_${COMPONENT_U}_COMPILE_FLAGS ${COMPILE_FLAGS} CACHE INTERNAL "Compilation flags for NT2 module ${COMPONENT}" FORCE)
  set(NT2_${COMPONENT_U}_LINK_FLAGS ${LINK_FLAGS} CACHE INTERNAL "Linking flags for NT2 module ${COMPONENT}" FORCE)

  mark_as_advanced(NT2_${COMPONENT_U}_INCLUDE_DIR NT2_${COMPONENT_U}_LIBRARY_DIR
                   NT2_${COMPONENT_U}_LIBRARIES
                   NT2_${COMPONENT_U}_COMPILE_FLAGS NT2_${COMPONENT_U}_LINK_FLAGS
                  )

  # Debug info
  nt2_find_log("${COMPONENT} variables:")
  nt2_find_log(" - NT2_${COMPONENT_U}_FOUND = ${NT2_${COMPONENT_U}_FOUND}")
  nt2_find_log(" - NT2_${COMPONENT_U}_INCLUDE_DIR = ${NT2_${COMPONENT_U}_INCLUDE_DIR}")
  nt2_find_log(" - NT2_${COMPONENT_U}_LIBRARY_DIR = ${NT2_${COMPONENT_U}_LIBRARY_DIR}")
  nt2_find_log(" - NT2_${COMPONENT_U}_LIBRARIES = ${NT2_${COMPONENT_U}_LIBRARIES}")
  nt2_find_log(" - NT2_${COMPONENT_U}_COMPILE_FLAGS = ${NT2_${COMPONENT_U}_COMPILE_FLAGS}")
  nt2_find_log(" - NT2_${COMPONENT_U}_LINK_FLAGS = ${NT2_${COMPONENT_U}_LINK_FLAGS}")

  # Configure/build if source
  if(NT2_${COMPONENT_U}_ROOT)
    nt2_find_module_path_push()
    string(REPLACE "." "/" COMPONENT_PATH ${COMPONENT})
    if(IS_DIRECTORY ${NT2_${COMPONENT_U}_ROOT}/src)
      add_subdirectory(${NT2_${COMPONENT_U}_ROOT}/src ${NT2_BINARY_DIR}/modules/${COMPONENT_PATH}/src)
    else()
      file(MAKE_DIRECTORY ${NT2_BINARY_DIR}/modules/${COMPONENT_PATH}/src)
      file(WRITE ${NT2_BINARY_DIR}/modules/${COMPONENT_PATH}/src/CMakeLists.txt "include(NT2Module)\nnt2_module_source_setup(${COMPONENT})")
      add_subdirectory(${NT2_BINARY_DIR}/modules/${COMPONENT_PATH}/src ${NT2_BINARY_DIR}/modules/${COMPONENT_PATH}/src)
    endif()
    nt2_find_module_path_pop()
  endif()

endfunction()

function(nt2_find)

  set(NT2_FOUND 1)
  set(NT2_INCLUDE_DIR "")
  set(NT2_LIBRARY_DIR "")
  set(NT2_LIBRARIES "")
  set(NT2_COMPILE_FLAGS " ")
  set(NT2_LINK_FLAGS " ")

  if(NOT DEFINED NT2_BINARY_DIR)
    set(NT2_BINARY_DIR ${PROJECT_BINARY_DIR}/nt2)
  endif()
  if(NOT DEFINED NT2_BINARY_INCLUDE_DIR)
    set(NT2_BINARY_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/nt2/include)
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

  set(NT2_POSTCONFIGURE_TOINIT ${NT2_POSTCONFIGURE_INITED})

  # Initialize post-configuration engine if needed
  if(NOT NT2_POSTCONFIGURE_TOINIT)
    nt2_postconfigure_init()
  endif()

  # Search for all requested components
  nt2_find_modules(${ARGV})
  nt2_copy_parent( NT2_FOUND
                   NT2_INCLUDE_DIR NT2_LIBRARY_DIR
                   NT2_LIBRARIES
                   NT2_COMPILE_FLAGS NT2_LINK_FLAGS
                   NT2_BINARY_DIR
                 )

  # Run post-configuration commands if needed
  if(NOT NT2_POSTCONFIGURE_TOINIT)
    nt2_postconfigure_run()
  endif()

  find_file(NT2_USE_FILE UseNT2.cmake PATHS ${NT2_MODULE_PATH})

  if(NT2_FIND_REQUIRED AND NOT NT2_FOUND)
    message(FATAL_ERROR "NT2 was not found")
  endif()

endfunction()

nt2_find(${NT2_FIND_COMPONENTS})
