################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(nt2.add_library)
include(nt2.add_executable)

# this function defines variables containing the location
# where extra files should be installed
macro(nt2_module_install_setup)
  if(NOT UNIX)
    set( NT2_INSTALL_SHARE_DIR .
         CACHE PATH "Directory where to install extra files"
       )
  else()
    set( NT2_INSTALL_SHARE_DIR share/nt2
         CACHE PATH "Directory where to install extra files"
       )
  endif()

endmacro()

# this function must always be called in the source CMakeLists of a module.
# it sets up module component, installation, binary locations and puts the
# dependencies inside the current scope
macro(nt2_module_source_setup module)
  string(TOUPPER ${module} NT2_CURRENT_MODULE_U)

  set(NT2_CURRENT_MODULE ${module})
  set(LIBRARY_OUTPUT_PATH ${NT2_BINARY_DIR}/lib)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_OUTPUT_PATH})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_OUTPUT_PATH})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_OUTPUT_PATH})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH})

  include_directories(${NT2_${NT2_CURRENT_MODULE_U}_INCLUDE_DIR})
  link_directories(${NT2_${NT2_CURRENT_MODULE_U}_DEPENDENCIES_LIBRARY_DIR})
  link_libraries(${NT2_${NT2_CURRENT_MODULE_U}_DEPENDENCIES_LIBRARIES})
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${NT2_${NT2_CURRENT_MODULE_U}_DEPENDENCIES_COMPILE_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${NT2_${NT2_CURRENT_MODULE_U}_DEPENDENCIES_COMPILE_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${NT2_${NT2_CURRENT_MODULE_U}_DEPENDENCIES_LINK_FLAGS}")

  file(WRITE ${NT2_BINARY_DIR}/modules/${module}.manifest)

  # installation is only done when current project is NT2
  # or same as current module
  if(PROJECT_NAME MATCHES "^NT2")

    nt2_module_install_setup()

    # make dummy executable target with all sources for Visual Studio
    if(CMAKE_GENERATOR MATCHES "Visual Studio")
      option(NT2_USE_FOLDERS "Whether to use folders for Visual Studio solution (professional version only)" 0)
      set_property(GLOBAL PROPERTY USE_FOLDERS ${NT2_USE_FOLDERS})

      file(GLOB_RECURSE files RELATIVE ${NT2_${NT2_CURRENT_MODULE_U}_ROOT}
           ${NT2_${NT2_CURRENT_MODULE_U}_ROOT}/include/*.hpp ${NT2_${NT2_CURRENT_MODULE_U}_ROOT}/include/*.h
          )
      set(files_full)
      foreach(file ${files})
        get_filename_component(dir ${file} PATH)
        string(REPLACE "/" "\\" dir ${dir})
        source_group(${dir} FILES ${NT2_${NT2_CURRENT_MODULE_U}_ROOT}/${file})
        list(APPEND files_full ${NT2_${NT2_CURRENT_MODULE_U}_ROOT}/${file})
      endforeach()

      if(NOT EXISTS ${NT2_BINARY_DIR}/modules/dummy.cpp)
        file(WRITE ${NT2_BINARY_DIR}/modules/dummy.cpp)
      endif()
      add_library(${module}.sources EXCLUDE_FROM_ALL ${NT2_BINARY_DIR}/modules/dummy.cpp ${files_full})
      set_property(TARGET ${module}.sources PROPERTY FOLDER sources)
    endif()

    # set up component
    cpack_add_component(${module}
                        DEPENDS ${NT2_${NT2_CURRENT_MODULE_U}_DEPENDENCIES_EXTRA}
                       )

    # install headers, cmake modules and manifest
    install( DIRECTORY ${NT2_${NT2_CURRENT_MODULE_U}_ROOT}/include/
             DESTINATION include
             COMPONENT ${module}
             FILES_MATCHING PATTERN "*.hpp"
           )
    install( FILES ${NT2_BINARY_DIR}/modules/${module}.manifest
             DESTINATION ${NT2_INSTALL_SHARE_DIR}/modules
             COMPONENT ${module}
           )
    install( DIRECTORY ${NT2_${NT2_CURRENT_MODULE_U}_ROOT}/cmake
             DESTINATION ${NT2_INSTALL_SHARE_DIR}
             COMPONENT ${module}
             FILES_MATCHING PATTERN "*.cmake"
                            PATTERN "*.txt"
                            PATTERN "*.cpp"
           )
  endif()

endmacro()

# if they don't already exist, create a target and all of its logical parents
# e.g. foo.bar.baz.thing -> foo.baz.thing -> foo.thing -> thing
function(nt2_module_target_parent target)
  string(REGEX REPLACE "[^.]+\\.([^.]+)$" "\\1" parent_target ${target})
  string(REGEX REPLACE "^.*\\.([^.]+)$" "\\1" suffix ${parent_target})

  get_target_property(${target}_exists ${target} EXCLUDE_FROM_ALL)
  if(${target}_exists MATCHES "NOTFOUND$")
    add_custom_target(${target})
    set_property(TARGET ${target} PROPERTY FOLDER ${suffix})
  endif()

  if(NOT parent_target STREQUAL ${target})
    nt2_module_target_parent(${parent_target})
    add_dependencies(${parent_target} ${target})
  endif()
endfunction()

# sets/restore the variable CMAKE_BUILD_TYPE and its multi-configuration equivalent
macro(nt2_module_set_build_type BUILD_TYPE)
  if(CMAKE_CONFIGURATION_TYPES)
    set(OLD_CONFIGURATION_TYPES ${CMAKE_CONFIGURATION_TYPES})
    set(CMAKE_CONFIGURATION_TYPES ${BUILD_TYPE} CACHE STRING "" FORCE)
  else()
    set(OLD_BUILD_TYPE ${CMAKE_BUILD_TYPE})
    set(CMAKE_BUILD_TYPE ${BUILD_TYPE})
  endif()
endmacro()

macro(nt2_module_restore_build_type)
  if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES ${OLD_CONFIGURATION_TYPES} CACHE STRING "" FORCE)
  else()
    set(CMAKE_BUILD_TYPE ${OLD_BUILD_TYPE})
  endif()
endmacro()

# load a module directory and create associated targets
macro(nt2_module_dir dir)
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/CMakeLists.txt)
      add_subdirectory(${dir})
      if(NOT ${dir} STREQUAL doc)
        nt2_module_target_parent(${NT2_CURRENT_MODULE}.${dir})
      endif()
    endif()
endmacro()

# define various variables to select which tests to enable
macro(nt2_configure_tests)
  if(CMAKE_GENERATOR MATCHES "Ninja")
    set(NT2_WITH_TESTS_FULL_ 1)
  else()
    set(NT2_WITH_TESTS_FULL_ 0)
  endif()
  if(CMAKE_GENERATOR MATCHES "Make|Ninja")
    set(NT2_WITH_TESTS_ 1)
  else()
    set(NT2_WITH_TESTS_ 0)
  endif()
  option(NT2_WITH_TESTS "Enable benchmarks and unit tests" ${NT2_WITH_TESTS_})
  option(NT2_WITH_TESTS_FULL "Use one executable per test" ${NT2_WITH_TESTS_FULL_})
  option(NT2_WITH_TESTS_BENCH "Register benchmarks with ctest" OFF)
  option(NT2_WITH_TESTS_COVER "Enable cover tests" OFF)
  set(CMAKE_CROSSCOMPILING_CMD $ENV{CMAKE_CROSSCOMPILING_CMD})# CACHE STRING "Command to use to run test sin a cross-compiling setup")
  set(CMAKE_CROSSCOMPILING_HOST $ENV{CMAKE_CROSSCOMPILING_HOST})# CACHE STRING "Host name to connect to in order to run tests in a cross-compiling setup")

  if(NT2_WITH_TESTS_FULL)
    set(NT2_WITH_TESTS ON CACHE BOOL "Enable benchmarks and unit tests" FORCE)
  endif()

  if(NT2_WITH_TESTS)
    enable_testing()
    include(CTest)

    foreach(target bench unit cover)
      get_target_property(${target}_exists ${target} EXCLUDE_FROM_ALL)
      if(${target}_exists MATCHES "NOTFOUND$")
        add_custom_target(${target})
        set_property(TARGET ${target} PROPERTY FOLDER ${target})
      endif()
    endforeach()
  endif()
endmacro()

# main function to call in a module's root CMakeLists file
macro(nt2_module_main module)
  string(TOUPPER ${module} NT2_CURRENT_MODULE_U)
  set(NT2_${NT2_CURRENT_MODULE_U}_ROOT ${CMAKE_CURRENT_SOURCE_DIR}
      CACHE PATH "Root directory of the ${module} module's source" FORCE
     )
  mark_as_advanced(NT2_${NT2_CURRENT_MODULE_U}_ROOT)

  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL ${PROJECT_SOURCE_DIR})
    if(CMAKE_CONFIGURATION_TYPES)
      set(CMAKE_CONFIGURATION_TYPES Release Debug NT2Test NT2TestDebug NT2Bench CACHE STRING "" FORCE)
    endif()
    project(NT2_${NT2_CURRENT_MODULE_U})
    set(NT2_BINARY_DIR ${PROJECT_BINARY_DIR})
    nt2_postconfigure_init()
  endif()

  include(nt2.compiler.options)

  set(NT2_CURRENT_MODULE ${module})
  nt2_module_use_modules(${module})

  nt2_configure_tests()
  if(NT2_WITH_TESTS)
    nt2_module_dir(bench)
    nt2_module_dir(examples)
    nt2_module_dir(unit)

    if(NT2_WITH_TESTS_COVER)
      nt2_module_dir(cover)
    endif()
  endif()

  if(NT2_DOCUMENTATION_ENABLED)
    nt2_module_dir(doc)
  endif()

  if(PROJECT_NAME STREQUAL "NT2_${NT2_CURRENT_MODULE_U}")
    nt2_postconfigure_run()
  endif()
endmacro()

# add library to module, with both Release and Debug variants, and add those files for installation.
# defines -D${module_U}_SOURCE when compiling the source
# defines -D${module_U}_DYN_LINK when compiling as a shared library
macro(nt2_module_add_library libname)
  string(TOUPPER ${NT2_CURRENT_MODULE} NT2_CURRENT_MODULE_U)

  if(${libname} MATCHES "_d$")
    set(BUILD_TYPE Debug)
  elseif(NOT CMAKE_CONFIGURATION_TYPES)
    nt2_module_add_library("${libname}_d" ${ARGN})
    set(BUILD_TYPE Release)
  endif()

  if(DEFINED NT2_USE_STATIC_LIBS AND NOT DEFINED NT2_${NT2_CURRENT_MODULE_U}_USE_STATIC_LIBS)
    set(NT2_${NT2_CURRENT_MODULE_U}_USE_STATIC_LIBS NT2_USE_STATIC_LIBS)
  endif()

  set(library_keyword)
  if(DEFINED NT2_${NT2_CURRENT_MODULE_U}_USE_STATIC_LIBS)
    if(NT2_${NT2_CURRENT_MODULE_U}_USE_STATIC_LIBS)
      set(library_keyword SHARED)
      set(NT2_${NT2_CURRENT_MODULE_U}_DYN_LINK 1)
    else()
      set(library_keyword STATIC)
    endif()
  else()
    set(NT2_${NT2_CURRENT_MODULE_U}_DYN_LINK ${BUILD_SHARED_LIBS})
  endif()

  if(NOT CMAKE_CONFIGURATION_TYPES)
    nt2_add_library(${BUILD_TYPE} ${libname} ${library_keyword} ${ARGN})
  else()
    add_library(${libname} ${library_keyword} ${ARGN})
    set_property(TARGET ${libname} PROPERTY OUTPUT_NAME_DEBUG "${libname}_d")
  endif()

  set_property(TARGET ${libname} PROPERTY VERSION 3.0.0)
  set_property(TARGET ${libname} PROPERTY SOVERSION 3)
  set_property(TARGET ${libname} PROPERTY FOLDER lib)

  if(${NT2_CURRENT_MODULE} MATCHES "^boost\\.")
    string(REPLACE "." "_" macro_name ${NT2_CURRENT_MODULE_U})
  else()
    string(REPLACE "." "_" macro_name "NT2_${NT2_CURRENT_MODULE_U}")
  endif()
  set(FLAGS "-D${macro_name}_SOURCE")
  if(NT2_${NT2_CURRENT_MODULE_U}_DYN_LINK)
    set(FLAGS "${FLAGS} -D${macro_name}_DYN_LINK")
  endif()
  set_property(TARGET ${libname} PROPERTY COMPILE_FLAGS ${FLAGS})
  set_property(TARGET ${libname} PROPERTY LINK_FLAGS ${FLAGS})

  if(PROJECT_NAME MATCHES "^NT2")
    install( DIRECTORY ${NT2_BINARY_DIR}/lib
             DESTINATION . COMPONENT ${NT2_CURRENT_MODULE}
             FILES_MATCHING PATTERN "*${libname}.*"
           )
  endif()

endmacro()

# find some NT2 modules and use them in the current scope
# exits if not all modules were found
macro(nt2_module_use_modules)

  string(REGEX REPLACE "^.*/(.*)$" "\\1" component "${CMAKE_CURRENT_SOURCE_DIR}")
  if(NOT component STREQUAL ${NT2_CURRENT_MODULE})
    set(component_ " ${component}:")
  endif()

  #message(STATUS "[nt2.${NT2_CURRENT_MODULE}]${component_} checking dependencies...")

  find_package(NT2 COMPONENTS ${ARGN})
  if(NOT NT2_FOUND)
    message(STATUS "[nt2.${NT2_CURRENT_MODULE}] warning:${component_} dependencies not met, skipping")
    return()
  endif()
  include(${NT2_USE_FILE})
endmacro()

# use some link flags for all targets in directory
# usage similar to add_definitions
macro(nt2_module_use_link_flags)
  string(REPLACE ";" "\" \"" FLAGS "${ARGN}")
  set(FLAGS "\"${FLAGS}\"")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${FLAGS}")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${FLAGS}")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${FLAGS}")
endmacro()

# similar to add_executable, but only for tests or benchmarks
# will define targets and use PCH whenever possible
function(nt2_module_add_exe name)
  string(REGEX REPLACE "^(.*)\\.([^.]+)$" "\\1" basename ${name})
  string(REGEX REPLACE "^(.*)\\.([^.]+)$" "\\2" suffix ${name})

  set(build_type)
  if(suffix STREQUAL unit OR suffix STREQUAL cover OR suffix STREQUAL exhaustive)
    set(build_type NT2Test)
  elseif(suffix STREQUAL bench)
    set(build_type NT2Bench)
  elseif(suffix STREQUAL debug)
    set(build_type NT2TestDebug)
  endif()
  string(TOUPPER ${build_type} build_type_U)

  if(NT2_PCH_TARGET)
    set(ARGS)
    foreach(arg ${ARGN})
      list(APPEND ARGS ${build_type}/${arg})
      nt2_pch_file(${build_type} ${build_type}/${arg} ${arg})
    endforeach()
  else()
    set(ARGS ${ARGN})
  endif()

  if(CMAKE_CONFIGURATION_TYPES)
    nt2_add_executable(${build_type} ${name} EXCLUDE_FROM_ALL ${ARGS})
  else()
    add_executable(${name} EXCLUDE_FROM_ALL ${ARGS})
    set_property(TARGET ${name} PROPERTY COMPILE_FLAGS ${CMAKE_CXX_FLAGS_${build_type_U}})
    set_property(TARGET ${name} PROPERTY LINK_FLAGS ${CMAKE_EXE_LINKER_FLAGS_${build_type_U}})
  endif()
  set_property(TARGET ${name} PROPERTY FOLDER ${suffix})
  set_property(TARGET ${name} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${NT2_BINARY_DIR}/${suffix})
  set_property(TARGET ${name} PROPERTY RUNTIME_OUTPUT_DIRECTORY_${build_type_U} ${NT2_BINARY_DIR}/${suffix})

  nt2_module_target_parent(${name})

  # if full tests mode, also add debug targets for unit tests
  if(suffix STREQUAL unit AND NT2_WITH_TESTS_FULL AND NOT CMAKE_CONFIGURATION_TYPES)
    nt2_module_add_exe(${basename}.debug ${ARGN})
  endif()

endfunction()

# like nt2_module_add_exe but slightly different suffix management for examples
macro(nt2_module_add_example name)
  add_executable(${name} EXCLUDE_FROM_ALL ${ARGN})
  set_property(TARGET ${name} PROPERTY FOLDER examples)
  set_property(TARGET ${name} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${NT2_BINARY_DIR}/examples)

  if(NT2_PCH_TARGET)
    add_dependencies(${name} ${NT2_PCH_TARGET}_${build_type}.pch)
    add_dependencies(${name} ${NT2_PCH_FILE}})
  endif()

  string(REGEX REPLACE "[^.]+\\.sample$" "examples" suite ${name})
  nt2_module_target_parent(${suite})
  add_dependencies(${suite} ${name})
endmacro()

# define a suite of tests to build
# similar to nt2_module_add_exe, but will merge executables into a single one
# unless NT2_WITH_TESTS_FULL is set
macro(nt2_module_add_tests name)
  string(REGEX REPLACE "^(.*)\\.([^.]+)$" "\\1" prefix ${name})
  string(REGEX REPLACE "^(.*)\\.([^.]+)$" "\\2" suffix ${name})

  if(${ARGC} GREATER 1)

    if(NOT NT2_WITH_TESTS_FULL)
      create_test_sourcelist(${name}_files ${name}.tmp.cpp ${ARGN})
      set(${name}_files ${name}.cpp ${ARGN})
      set_property(SOURCE "${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp" PROPERTY COMPILE_DEFINITIONS "_CRT_SECURE_NO_WARNINGS=1")

      file(READ "${CMAKE_CURRENT_BINARY_DIR}/${name}.tmp.cpp" DATA)
      file(REMOVE "${CMAKE_CURRENT_BINARY_DIR}/${name}.tmp.cpp")
    endif()

    foreach(source ${ARGN})
      string(REGEX REPLACE "^([^/]+).cpp$" "\\1" basename ${source})

      if(NOT NT2_WITH_TESTS_FULL)
        string(REPLACE "int ${basename}(int, char*[]);" "extern \"C\" int nt2_test_${basename}(int, char*[]);" DATA "${DATA}")
        string(REGEX REPLACE "\"${basename}\",([ \r\n]+)${basename}" "\"${basename}\",\\1nt2_test_${basename}" DATA "${DATA}")
        set_property(SOURCE ${source} PROPERTY COMPILE_DEFINITIONS NT2_UNIT_MAIN=nt2_test_${basename})
        set(exe ${name})
        set(arg ${basename})
      else()
        nt2_module_add_exe(${prefix}.${basename}.${suffix} ${source})
        set(exe ${prefix}.${basename}.${suffix})
        set(arg)
      endif()

      if(NOT suffix STREQUAL bench OR NT2_WITH_TESTS_BENCH)
        if(CMAKE_CROSSCOMPILING AND CMAKE_CROSSCOMPILING_HOST)
          add_test(${prefix}.${basename}-${suffix} /bin/sh -c
                   "scp \"${NT2_BINARY_DIR}/${suffix}/${exe}\" ${CMAKE_CROSSCOMPILING_HOST}:/tmp && ssh ${CMAKE_CROSSCOMPILING_HOST} /tmp/${exe} ${arg} && ssh ${CMAKE_CROSSCOMPILING_HOST} rm /tmp/${exe}"
                  )
        elseif(CMAKE_CROSSCOMPILING AND CMAKE_CROSSCOMPILING_CMD)
          add_test(${prefix}.${basename}-${suffix} ${CMAKE_CROSSCOMPILING_CMD} ${NT2_BINARY_DIR}/${suffix}/${exe} ${arg})
        else()
          add_test(${prefix}.${basename}-${suffix} ${NT2_BINARY_DIR}/${suffix}/${exe} ${arg})
        endif()

        if(NT2_WITH_TESTS_ALL)
          set_property(TARGET ${exe} PROPERTY EXCLUDE_FROM_ALL OFF)
        endif()

      endif()
    endforeach()

    if(NOT NT2_WITH_TESTS_FULL)
      nt2_module_add_exe(${name} ${${name}_files})

      set(OLD_DATA)
      if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp")
        file(READ "${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp" OLD_DATA)
      endif()
      if(NOT "${OLD_DATA}" STREQUAL "${DATA}")
        file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp" "${DATA}")
      endif()
    endif()

  endif()

endmacro()

# mark a header file for installation
# useful when some header files are generated
macro(nt2_module_install_file header)
  string(TOUPPER ${NT2_CURRENT_MODULE} NT2_CURRENT_MODULE_U)

  if(PROJECT_NAME MATCHES "^NT2")
    string(REGEX REPLACE "^(.*)/[^/]+$" "\\1" ${header}_path ${header})
    install(FILES ${NT2_BINARY_DIR}/include/${header}
            DESTINATION include/${${header}_path}
            COMPONENT ${NT2_CURRENT_MODULE}
           )
  endif()
endmacro()

# generate files according to the toolbox layout
# e.g. all files <x>.hpp in nt2/toolbox/<toolbox>/functions/
#      get aggregated to nt2/toolbox/<toolbox>/include/functions/<x>.hpp
# will also do the same for constants, and will generate the file nt2/toolbox/<toolbox>/<toolbox>.hpp
# nt2/toolbox/<toolbox>/include/functions/scalar/<x>.hpp and nt2/toolbox/<toolbox>/include/functions/simd/<x>.hpp
# are also generated to restrict the amount of includes to only those required in scalar and simd respectively.
#
# if is_sys is set to 1, files will also be aggregated in nt2/include/functions
macro(nt2_module_configure_toolbox toolbox is_sys)
  if(NT2_CURRENT_MODULE MATCHES "^boost[.]")
    set(prefix "boost/simd")
  else()
    set(prefix "nt2")
  endif()

  set(reduce)
  foreach(component functions constants)

    set(extra)
    foreach(arg ${ARGN})
      list(APPEND extra ${arg}/${component})
    endforeach()

    set(postfix)
    if(${is_sys})
      set(postfix --out ${prefix}/include/${component})
    endif()

    nt2_module_postconfigure(gather_includes --ignore impl --ignore details --ignore preprocessed
                                             ${prefix}/toolbox/${toolbox}/${component} ${extra}
                                             --out ${prefix}/toolbox/${toolbox}/include/${component}
                                             ${prefix}/toolbox/${toolbox}/include/${component}
                                             --out ${prefix}/toolbox/${toolbox}/${component}.hpp
                                             ${postfix}
                            )

    list(APPEND reduce ${prefix}/toolbox/${toolbox}/${component}.hpp)
  endforeach()

  nt2_module_postconfigure(gather_includes ${reduce}
                                           --out ${prefix}/toolbox/${toolbox}/${toolbox}.hpp
                          )

  foreach(component scalar simd)

    set(extra)
    foreach(arg ${ARGN})
      list(APPEND extra ${arg}/functions/generic ${arg}/functions/scalar ${arg}/functions/${component})
    endforeach()

    set(postfix)
    if(${is_sys})
      set(postfix --out ${prefix}/include/functions/${component})
    endif()

    nt2_module_postconfigure(gather_includes --ignore impl --ignore details --ignore preprocessed
                                             --max 1 ${prefix}/toolbox/${toolbox}/functions
                                             ${prefix}/toolbox/${toolbox}/functions/generic
                                             ${prefix}/toolbox/${toolbox}/functions/scalar
                                             ${prefix}/toolbox/${toolbox}/functions/${component}
                                             ${extra}
                                             --out ${prefix}/toolbox/${toolbox}/include/functions/${component}
                                             ${prefix}/toolbox/${toolbox}/include/functions/${component}
                                             ${postfix}
                            )
  endforeach()

endmacro()

# same as configure_file, but puts it in the right location and marks
# the generated header for installation
macro(nt2_module_configure_file cmake_file header)
  configure_file(${cmake_file} ${NT2_BINARY_DIR}/include_tmp/${header})
  nt2_module_install_file(${header})
endmacro()

# adapt a Boost.SIMD toolbox into a NT2 toolbox
# for each function in the Boost.SIMD toolbox, an associated header is generated in NT2
# unless it already exists in the source.
macro(nt2_module_simd_toolbox name)
  string(TOUPPER ${name} name_U)
  set(INCLUDE_DIRECTORIES)
  foreach(module core.${name} boost.simd.${name})
    string(TOUPPER ${module} module_U)
    list(APPEND INCLUDE_DIRECTORIES ${NT2_${module_U}_ROOT}/include)
  endforeach()
  foreach(dir ${INCLUDE_DIRECTORIES})
    file(GLOB function_files RELATIVE ${dir}/boost/simd/toolbox/${name}/functions ${dir}/boost/simd/toolbox/${name}/functions/*.hpp)
    foreach(file ${function_files})
      set(already_there)
      foreach(dir2 ${INCLUDE_DIRECTORIES})
        if(EXISTS ${dir2}/nt2/toolbox/${name}/functions/${file})
          set(already_there 1)
        endif()
      endforeach()
      if(NOT already_there)
        string(REGEX REPLACE ".hpp" "" file ${file})
        string(TOUPPER ${file} file_U)
        file(WRITE ${NT2_BINARY_DIR}/include_tmp/nt2/toolbox/${name}/functions/${file}.hpp
                   "//==============================================================================\n"
                   "//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II\n"
                   "//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI\n"
                   "//\n"
                   "//          Distributed under the Boost Software License, Version 1.0.\n"
                   "//                 See accompanying file LICENSE.txt or copy at\n"
                   "//                     http://www.boost.org/LICENSE_1_0.txt\n"
                   "//==============================================================================\n"
                   "#ifndef NT2_TOOLBOX_${name_U}_FUNCTIONS_${file_U}_HPP_INCLUDED\n"
                   "#define NT2_TOOLBOX_${name_U}_FUNCTIONS_${file_U}_HPP_INCLUDED\n"
                   "\n"
                   "#include <boost/simd/toolbox/${name}/include/functions/${file}.hpp>\n"
                   "#include <nt2/include/functor.hpp>\n"
                   "\n"
                   "namespace nt2\n"
                   "{\n"
                   "  namespace tag\n"
                   "  {\n"
                   "    using boost::simd::tag::${file}_;\n"
                   "  }\n"
                   "\n"
                   "  using boost::simd::${file};\n"
                   "}\n"
                   "\n"
                   "#endif\n"
            )
      endif()
    endforeach()

    file(GLOB constant_files RELATIVE ${dir}/boost/simd/toolbox/${name}/constants ${dir}/boost/simd/toolbox/${name}/constants/*.hpp)
    foreach(file ${constant_files})
    set(already_there)
      foreach(dir2 ${INCLUDE_DIRECTORIES})
        if(EXISTS ${dir2}/nt2/toolbox/${name}/constants/${file})
          set(already_there 1)
        endif()
      endforeach()
      if(NOT already_there)
        string(REGEX REPLACE ".hpp" "" file ${file})
        string(TOUPPER ${file} file_U)
        string(LENGTH ${file} len)
        math(EXPR len "${len}-1")
        string(SUBSTRING ${file_U} 0 1 file_1)
        string(SUBSTRING ${file} 1 ${len} file_2)
        set(file_c "${file_1}${file_2}")
        file(WRITE ${NT2_BINARY_DIR}/include_tmp/nt2/toolbox/${name}/constants/${file}.hpp
                   "//==============================================================================\n"
                   "//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II\n"
                   "//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI\n"
                   "//\n"
                   "//          Distributed under the Boost Software License, Version 1.0.\n"
                   "//                 See accompanying file LICENSE.txt or copy at\n"
                   "//                     http://www.boost.org/LICENSE_1_0.txt\n"
                   "//==============================================================================\n"
                   "#ifndef NT2_TOOLBOX_${name_U}_CONSTANTS_${file_U}_HPP_INCLUDED\n"
                   "#define NT2_TOOLBOX_${name_U}_CONSTANTS_${file_U}_HPP_INCLUDED\n"
                   "\n"
                   "#include <boost/simd/toolbox/${name}/include/constants/${file}.hpp>\n"
                   "#include <nt2/include/functor.hpp>\n"
                   "\n"
                   "namespace nt2\n"
                   "{\n"
                   "  namespace tag\n"
                   "  {\n"
                   "    using boost::simd::tag::${file_c};\n"
                   "  }\n"
                   "\n"
                   "  using boost::simd::${file_c};\n"
                   "}\n"
                   "\n"
                   "#endif\n"
            )
      endif()
    endforeach()

    file(GLOB include_files1 RELATIVE ${dir}/boost/simd/toolbox/${name}/include/functions ${dir}/boost/simd/toolbox/${name}/include/functions/*.hpp)
    foreach(file ${include_files1})
      file(READ ${dir}/boost/simd/toolbox/${name}/include/functions/${file} file_content)
      string(REPLACE "boost/simd/" "nt2/" file_content "${file_content}")
      string(REPLACE "BOOST_SIMD_" "NT2_" file_content "${file_content}")
      string(REPLACE "namespace boost { namespace simd" "namespace nt2" file_content "${file_content}")
      string(REPLACE "} }" "}" file_content "${file_content}")
      file(WRITE ${NT2_BINARY_DIR}/include_tmp/nt2/toolbox/${name}/include/functions/${file} "${file_content}")
    endforeach()

    file(GLOB include_files2 RELATIVE ${dir}/boost/simd/toolbox/${name}/include/constants ${dir}/boost/simd/toolbox/${name}/include/constants/*.hpp)
    foreach(file ${include_files2})
      file(READ ${dir}/boost/simd/toolbox/${name}/include/constants/${file} file_content)
      string(REPLACE "boost/simd/" "nt2/" file_content "${file_content}")
      string(REPLACE "BOOST_SIMD_" "NT2_" file_content "${file_content}")
      string(REPLACE "namespace boost { namespace simd" "namespace nt2" file_content "${file_content}")
      string(REPLACE "} }" "}" file_content "${file_content}")
      file(WRITE ${NT2_BINARY_DIR}/include_tmp/nt2/toolbox/${name}/include/constants/${file} "${file_content}")
    endforeach()
  endforeach()

  nt2_module_configure_toolbox(${name} 1 boost/simd/toolbox/${name})
endmacro()

# build a tool
macro(nt2_module_tool_setup tool)

  if(NOT NT2_SOURCE_ROOT)
    message(FATAL_ERROR "[nt2] tool ${tool} was not found and cannot be built")
  endif()

  get_property(NT2_TOOL_${tool}_BUILT GLOBAL PROPERTY NT2_TOOL_${tool}_BUILT)
  if(NOT NT2_TOOL_${tool}_BUILT)

    define_property(GLOBAL PROPERTY NT2_TOOL_${tool}_BUILT
                    BRIEF_DOCS "Whether nt2 tool ${tool} has already been built"
                    FULL_DOCS "Global flag to avoid building nt2 tool ${tool} multiple times"
                   )
    set_property(GLOBAL PROPERTY NT2_TOOL_${tool}_BUILT 1)

    message(STATUS "[nt2] building tool ${tool}")
    file(MAKE_DIRECTORY ${NT2_BINARY_DIR}/tools/${tool})

    if(NOT DEFINED NT2_TOOL_DEBUG)
      set(NT2_TOOL_DEBUG $ENV{NT2_TOOL_DEBUG})
    endif()
    if(NT2_TOOL_DEBUG)
      set(NT2_TOOL_CONFIG Debug)
    else()
      set(NT2_TOOL_CONFIG Release)
    endif()

    set(BUILD_OPTION)
    if(NOT CMAKE_CONFIGURATION_TYPES)
      set(BUILD_OPTION -DCMAKE_BUILD_TYPE=${NT2_TOOL_CONFIG})
    endif()
    if(Boost_INCLUDE_DIR)
      list(APPEND BUILD_OPTION -DBoost_INCLUDE_DIR=${Boost_INCLUDE_DIR})
    endif()
    if(NOT CMAKE_CROSSCOMPILING)
      list(APPEND BUILD_OPTION -G ${CMAKE_GENERATOR})
    endif()

    execute_process(COMMAND ${CMAKE_COMMAND}
                            ${BUILD_OPTION}
                            ${NT2_SOURCE_ROOT}/tools/${tool}
                    WORKING_DIRECTORY ${NT2_BINARY_DIR}/tools/${tool}
                    OUTPUT_VARIABLE tool_configure_out
                    RESULT_VARIABLE tool_configure
                   )

    if(tool_configure)
      message("${tool_configure_out}")
      message(FATAL_ERROR "[nt2] configuring tool ${tool} failed")
    endif()

    execute_process(COMMAND ${CMAKE_COMMAND} --build . --config ${NT2_TOOL_CONFIG}
                    WORKING_DIRECTORY ${NT2_BINARY_DIR}/tools/${tool}
                    OUTPUT_VARIABLE tool_build_out
                    RESULT_VARIABLE tool_build
                   )

    if(tool_build)
      message("${tool_build_out}")
      message(FATAL_ERROR "[nt2] building tool ${tool} failed")
    endif()

    if(PROJECT_NAME MATCHES "^NT2")
      install( PROGRAMS ${NT2_BINARY_DIR}/tools/${tool}/${tool}${CMAKE_EXECUTABLE_SUFFIX}
               DESTINATION tools/${tool}
               COMPONENT tools
             )
    endif()

  endif()

endmacro()

# use a tool, build it if not found
macro(nt2_module_tool tool)
  string(TOUPPER ${tool} tool_U)

  find_program(NT2_TOOL_${tool_U} ${tool} PATHS ${NT2_ROOT}/tools/${tool} NO_DEFAULT_PATH)
  mark_as_advanced(NT2_TOOL_${tool_U})
  if(NOT NT2_TOOL_${tool_U})
    nt2_module_tool_setup(${tool})
    set(NT2_TOOL_${tool_U} ${NT2_BINARY_DIR}/tools/${tool}/${tool})
  endif()
  execute_process(COMMAND ${NT2_TOOL_${tool_U}} ${ARGN})

endmacro()

# mark a tool command to execute at the end of the configuration
# nt2_postconfigure_init must be called before calling this function
macro(nt2_module_postconfigure)

  string(REPLACE ";" " " args "${ARGN}")
  file(APPEND ${NT2_BINARY_DIR}/modules/${NT2_CURRENT_MODULE}.manifest "${args}\n")

endmacro()

# initialize the post-configuration system
macro(nt2_postconfigure_init)

  include(nt2.doc)

  define_property(GLOBAL PROPERTY NT2_POSTCONFIGURE_INITED
                  BRIEF_DOCS "Whether nt2_postconfigure_init has already been called"
                  FULL_DOCS "Global flag to avoid running postconfigure multiple times"
                 )
  set_property(GLOBAL PROPERTY NT2_POSTCONFIGURE_INITED 1)
  set(NT2_FOUND_COMPONENTS "" CACHE INTERNAL "" FORCE)

  if(PROJECT_NAME MATCHES "^NT2")
    set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "ExecWait '\\\"$INSTDIR\\\\tools\\\\postconfigure\\\\postconfigure.exe\\\" \\\"$INSTDIR\\\"'")
    include(CPack)
    cpack_add_component(tools REQUIRED)

    # global cmake files install
    nt2_module_install_setup()
    install( DIRECTORY ${PROJECT_SOURCE_DIR}/cmake
             DESTINATION ${NT2_INSTALL_SHARE_DIR}
             FILES_MATCHING PATTERN "*.cmake"
                            PATTERN "*.txt"
                            PATTERN "*.cpp"
           )
  endif()

endmacro()

# run the post-configuration step.
# runs all tool commands registered with nt2_module_postconfigure
macro(nt2_postconfigure_run)

  message(STATUS "[nt2] running post-configuration commands")

  foreach(module ${NT2_FOUND_COMPONENTS})
    string(TOUPPER ${module} module_U)
    if(NT2_${module_U}_ROOT)
      list(APPEND postconfigure_prefix "-I${NT2_${module_U}_ROOT}/include")
    endif()
  endforeach()
  list(APPEND postconfigure_prefix "${NT2_BINARY_DIR}/include_tmp")

  foreach(module ${NT2_FOUND_COMPONENTS})
    if(EXISTS ${NT2_BINARY_DIR}/modules/${module}.manifest)
      set(file "${NT2_BINARY_DIR}/modules/${module}.manifest")
    else()
      set(file "${NT2_ROOT}/modules/${module}.manifest")
    endif()

    file(STRINGS ${file} commands)
    foreach(command ${commands})
      string(REGEX REPLACE "^([^ ]+) (.*)$" "\\1" tool ${command})
      string(REGEX REPLACE "^([^ ]+) (.*)$" "\\2" args ${command})
      string(REPLACE " " ";" args ${args})

      nt2_module_tool(${tool} ${postconfigure_prefix} ${args})

    endforeach()
  endforeach()

  if(IS_DIRECTORY ${NT2_BINARY_DIR}/include_tmp)
    nt2_module_tool(move_reuse ${NT2_BINARY_DIR}/include_tmp ${NT2_BINARY_DIR}/include)
  endif()

  if(PROJECT_NAME MATCHES "^NT2")

    cpack_add_component(postconfigured
                        HIDDEN DISABLED
                       )

    install( DIRECTORY ${NT2_BINARY_DIR}/include/
             DESTINATION include
             COMPONENT postconfigured
             FILES_MATCHING PATTERN "*.hpp"
           )

  endif()

endmacro()
