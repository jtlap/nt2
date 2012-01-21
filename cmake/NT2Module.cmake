################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(nt2.add_library)

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
  set(NT2_CURRENT_FLAGS "${NT2_CURRENT_FLAGS} ${NT2_${NT2_CURRENT_MODULE_U}_FLAGS}")
  
  file(WRITE ${NT2_BINARY_DIR}/modules/${module}.manifest)
  
  # installation is only done when current project is NT2
  # or same as current module
  if(PROJECT_NAME STREQUAL NT2 OR PROJECT_NAME STREQUAL "NT2_${NT2_CURRENT_MODULE_U}")

    nt2_module_install_setup()

    # make dummy executable target with all sources for Visual Studio
    if(CMAKE_GENERATOR MATCHES "Visual Studio")
      option(NT2_USE_FOLDERS "Whether to use folders for Visual Studio solution (professional version only)" 0)
      set_property(GLOBAL PROPERTY USE_FOLDERS ${NT2_USE_FOLDERS})
    
      file(GLOB_RECURSE files RELATIVE ${NT2_${NT2_CURRENT_MODULE_U}_ROOT}
           ${NT2_${NT2_CURRENT_MODULE_U}_ROOT}/include/*.hpp ${NT2_${NT2_CURRENT_MODULE_U}_ROOT}/include/*.h
           *.hpp *.h
           *.cpp *.c
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
      add_executable(${module}.sources EXCLUDE_FROM_ALL ${NT2_BINARY_DIR}/modules/dummy.cpp ${files_full})
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

function(nt2_module_target_parent target)
  string(REGEX REPLACE "[^.]+\\.([^.]+)$" "\\1" parent_target ${target})
  string(REGEX REPLACE "^.*\\.([^.]+)$" "\\1" suffix ${parent_target})
  
  if(NOT parent_target STREQUAL ${target})
    get_target_property(${parent_target}_exists ${parent_target} EXCLUDE_FROM_ALL)
    if(${parent_target}_exists MATCHES "NOTFOUND$")
      add_custom_target(${parent_target})
      set_property(TARGET ${parent_target} PROPERTY FOLDER ${suffix})
    endif()
    add_dependencies(${parent_target} ${target})
  
    nt2_module_target_parent(${parent_target})
  endif()
  
endfunction()

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

macro(nt2_module_dir dir)
  if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${dir})
      add_custom_target(${NT2_CURRENT_MODULE}.${dir})
      set_property(TARGET ${NT2_CURRENT_MODULE}.${dir} PROPERTY FOLDER ${dir})
      nt2_module_target_parent(${NT2_CURRENT_MODULE}.${dir})

      if(${dir} STREQUAL bench)
        set(BUILD_TYPE NT2Bench)
      else()
        set(BUILD_TYPE NT2Test)
      endif()

      nt2_module_set_build_type(${BUILD_TYPE})
      project(${NT2_CURRENT_MODULE}.${dir}) # would be better in directory
      add_subdirectory(${dir})
      nt2_module_restore_build_type()
    endif()
endmacro()

macro(nt2_configure_tests)
  if(CMAKE_GENERATOR MATCHES "Make")
    set(NT2_WITH_TESTS_ 1)
  else()
    set(NT2_WITH_TESTS_ 0)
  endif()
  option(NT2_WITH_TESTS "Enable benchmarks and unit tests" ${NT2_WITH_TESTS_})
  option(NT2_WITH_TESTS_FULL "Use one executable per test" OFF)
  option(NT2_WITH_TESTS_BENCH "Register benchmarks with ctest" OFF)
  option(NT2_WITH_TESTS_COVER "Enable cover tests" OFF)
  set(CMAKE_CROSSCOMPILING_HOST $ENV{CMAKE_CROSSCOMPILING_HOST} CACHE STRING "Host name to connect to in order to run tests in a cross-compiling setup")

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

macro(nt2_module_main module)
  string(TOUPPER ${module} NT2_CURRENT_MODULE_U)
  set(NT2_${NT2_CURRENT_MODULE_U}_ROOT ${CMAKE_CURRENT_SOURCE_DIR}
      CACHE PATH "Root directory of the ${module} module's source" FORCE
     )
  mark_as_advanced(NT2_${NT2_CURRENT_MODULE_U}_ROOT)
    
  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL ${PROJECT_SOURCE_DIR})
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
  
  if(PROJECT_NAME STREQUAL "NT2_${NT2_CURRENT_MODULE_U}")
    nt2_postconfigure_run()
  endif()
endmacro()

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
    string(REPLACE "." "__" macro_name "NT2_${NT2_CURRENT_MODULE_U}")
  endif()
  set(FLAGS "${NT2_CURRENT_FLAGS} -D${macro_name}_SOURCE")
  if(NT2_${NT2_CURRENT_MODULE_U}_DYN_LINK)
    set(FLAGS "${FLAGS} -D${macro_name}_DYN_LINK")
  endif()
  set_property(TARGET ${libname} PROPERTY COMPILE_FLAGS ${FLAGS})

  if(PROJECT_NAME STREQUAL NT2 OR PROJECT_NAME STREQUAL "NT2_${NT2_CURRENT_MODULE_U}")
    install( DIRECTORY ${NT2_BINARY_DIR}/lib
             DESTINATION . COMPONENT ${NT2_CURRENT_MODULE}
             FILES_MATCHING PATTERN "*${libname}.*"
           )
  endif()

endmacro()

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

  include_directories(${NT2_INCLUDE_DIR})
  link_directories(${NT2_LIBRARY_DIR})
  link_libraries(${NT2_LIBRARIES})
  set(NT2_CURRENT_FLAGS "${NT2_CURRENT_FLAGS} ${NT2_FLAGS}")
endmacro()

macro(nt2_module_add_exe name)
  string(REGEX REPLACE "^(.*)\\.([^.]+)$" "\\2" suffix ${name})
  
  add_executable(${name} EXCLUDE_FROM_ALL ${ARGN})
  set_property(TARGET ${name} PROPERTY FOLDER ${suffix})
  set_property(TARGET ${name} PROPERTY COMPILE_FLAGS ${NT2_CURRENT_FLAGS})
  set_property(TARGET ${name} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${NT2_BINARY_DIR}/${suffix})

  set(BUILD_TYPE)
  if(suffix STREQUAL unit OR suffix STREQUAL cover)
    set(BUILD_TYPE NT2TEST)
  elseif(suffix STREQUAL bench)
    set(BUILD_TYPE NT2BENCH)
  endif()
  if(BUILD_TYPE)
    set_property(TARGET ${name} PROPERTY RUNTIME_OUTPUT_DIRECTORY_${BUILD_TYPE} ${NT2_BINARY_DIR}/${suffix})
  endif()

  nt2_module_target_parent(${name})
  
endmacro()

# like add_exe but slightly different suffix management
macro(nt2_module_add_example name)
  add_executable(${name} EXCLUDE_FROM_ALL ${ARGN})
  set_property(TARGET ${name} PROPERTY FOLDER examples)
  set_property(TARGET ${name} PROPERTY COMPILE_FLAGS ${NT2_CURRENT_FLAGS})
  set_property(TARGET ${name} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${NT2_BINARY_DIR}/examples)

  string(REGEX REPLACE "\\.sample$" ".examples" suite ${name})
  nt2_module_target_parent(${suite})
endmacro()

macro(nt2_module_add_tests name)  
  string(REGEX REPLACE "^(.*)\\.([^.]+)$" "\\1" prefix ${name})
  string(REGEX REPLACE "^(.*)\\.([^.]+)$" "\\2" suffix ${name})
  
  if(${ARGC} GREATER 1)
  
    if(NOT NT2_WITH_TESTS_FULL)
      create_test_sourcelist(${name}_files ${name}.tmp.cpp ${ARGN})
      set(${name}_files ${name}.cpp ${ARGN})
      set_property(SOURCE "${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp" PROPERTY COMPILE_DEFINITIONS "_CRT_SECURE_NO_WARNINGS=1")
      nt2_module_add_exe(${name} ${${name}_files})
      
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
        else()
          add_test(${prefix}.${basename}-${suffix} ${NT2_BINARY_DIR}/${suffix}/${exe} ${arg})
        endif()
        
        if(NT2_WITH_TESTS_ALL)
          set_property(TARGET ${exe} PROPERTY EXCLUDE_FROM_ALL OFF)
        endif()
        
      endif()
    endforeach()
    
    if(NOT NT2_WITH_TESTS_FULL)
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

macro(nt2_module_install_file header)
  string(TOUPPER ${NT2_CURRENT_MODULE} NT2_CURRENT_MODULE_U)

  if(PROJECT_NAME STREQUAL NT2 OR PROJECT_NAME STREQUAL "NT2_${NT2_CURRENT_MODULE_U}")
    string(REGEX REPLACE "^(.*)/[^/]+$" "\\1" ${header}_path ${header})
    install(FILES ${NT2_BINARY_DIR}/include/${header}
            DESTINATION include/${${header}_path}
            COMPONENT ${NT2_CURRENT_MODULE}
           )
  endif()
endmacro()

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
  
endmacro()

macro(nt2_module_configure_file cmake_file header)
  configure_file(${cmake_file} ${NT2_BINARY_DIR}/include_tmp/${header})
  nt2_module_install_file(${header})
endmacro()

macro(nt2_module_simd_toolbox name)
  string(TOUPPER ${name} name_U)
  set(INCLUDE_DIRECTORIES)
  foreach(module ${name} boost.simd.${name})
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
      string(REPLACE "boost/simd/" "nt2/" file_content ${file_content})
      string(REPLACE "BOOST_SIMD_" "NT2_" file_content ${file_content})
      file(WRITE ${NT2_BINARY_DIR}/include_tmp/nt2/toolbox/${name}/include/functions/${file} ${file_content})
    endforeach()
  
    file(GLOB include_files2 RELATIVE ${dir}/boost/simd/toolbox/${name}/include/constants ${dir}/boost/simd/toolbox/${name}/include/constants/*.hpp)
    foreach(file ${include_files2})
      file(READ ${dir}/boost/simd/toolbox/${name}/include/constants/${file} file_content)
      string(REPLACE "boost/simd/" "nt2/" file_content ${file_content})
      string(REPLACE "BOOST_SIMD_" "NT2_" file_content ${file_content})
      file(WRITE ${NT2_BINARY_DIR}/include_tmp/nt2/toolbox/${name}/include/constants/${file} ${file_content})
    endforeach()
  endforeach()
    
  nt2_module_configure_toolbox(${name} 1 boost/simd/toolbox/${name})
endmacro()

macro(nt2_module_tool_setup tool)

  get_property(NT2_TOOL_${tool}_BUILT GLOBAL PROPERTY NT2_TOOL_${tool}_BUILT)
  if(NOT NT2_TOOL_${tool}_BUILT)

    define_property(GLOBAL PROPERTY NT2_TOOL_${tool}_BUILT
                    BRIEF_DOCS "Whether nt2 tool ${tool} has already been built"
                    FULL_DOCS "Global flag to avoid building nt2 tool ${tool} multiple times"
                   )
    set_property(GLOBAL PROPERTY NT2_TOOL_${tool}_BUILT 1)

    message(STATUS "[nt2] building tool ${tool}")
    file(MAKE_DIRECTORY ${NT2_BINARY_DIR}/tools/${tool})
  
    set(BUILD_OPTION)
    if(NOT CMAKE_CONFIGURATION_TYPES)
      set(BUILD_OPTION -DCMAKE_BUILD_TYPE=Release)
    endif()

    execute_process(COMMAND ${CMAKE_COMMAND}
                            ${BUILD_OPTION}
                            -G ${CMAKE_GENERATOR}
                            ${NT2_SOURCE_ROOT}/tools/${tool}
                    WORKING_DIRECTORY ${NT2_BINARY_DIR}/tools/${tool}
                    OUTPUT_VARIABLE tool_configure_out
                    RESULT_VARIABLE tool_configure
                   )

    if(tool_configure)
      message("${tool_configure_out}")
      message(FATAL_ERROR "[nt2] configuring tool ${tool} failed")
    endif()

    execute_process(COMMAND ${CMAKE_COMMAND} --build . --config Release
                    WORKING_DIRECTORY ${NT2_BINARY_DIR}/tools/${tool}
                    OUTPUT_VARIABLE tool_build_out
                    RESULT_VARIABLE tool_build
                   )
                 
    if(tool_build)
      message("${tool_build_out}")
      message(FATAL_ERROR "[nt2] building tool ${tool} failed")
    endif()

    if(PROJECT_NAME STREQUAL NT2 OR PROJECT_NAME STREQUAL "NT2_${NT2_CURRENT_MODULE_U}")
      install( FILES ${NT2_BINARY_DIR}/tools/${tool}/${tool}${CMAKE_EXECUTABLE_SUFFIX}
               DESTINATION tools/${tool}
               COMPONENT tools
             )
    endif()

  endif()

endmacro()

macro(nt2_module_tool tool)

  nt2_module_tool_setup(${tool})
  execute_process(COMMAND ${NT2_BINARY_DIR}/tools/${tool}/${tool} ${ARGN})

endmacro()

macro(nt2_module_postconfigure)

  string(REPLACE ";" " " args "${ARGN}")
  file(APPEND ${NT2_BINARY_DIR}/modules/${NT2_CURRENT_MODULE}.manifest "${args}\n")

endmacro()

macro(nt2_postconfigure_init)

  define_property(GLOBAL PROPERTY NT2_POSTCONFIGURE_INITED
                  BRIEF_DOCS "Whether nt2_postconfigure_init has already been called"
                  FULL_DOCS "Global flag to avoid running postconfigure multiple times"
                 )
  set_property(GLOBAL PROPERTY NT2_POSTCONFIGURE_INITED 1)
  set(NT2_FOUND_COMPONENTS "" CACHE INTERNAL "" FORCE)

  if(PROJECT_NAME STREQUAL NT2 OR PROJECT_NAME STREQUAL "NT2_${NT2_CURRENT_MODULE_U}")
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

    # postconfigure is a target because it's only required to install, not to configure
    file(MAKE_DIRECTORY ${NT2_BINARY_DIR}/tools/postconfigure)
    install( FILES ${NT2_BINARY_DIR}/tools/postconfigure/postconfigure${CMAKE_EXECUTABLE_SUFFIX}
             DESTINATION tools/postconfigure
             COMPONENT tools
             OPTIONAL
           )

    set(BUILD_OPTION)
    if(NOT CMAKE_CONFIGURATION_TYPES)
      set(BUILD_OPTION -DCMAKE_BUILD_TYPE=Release)
    endif()
             
    add_custom_target(postconfigure
                      COMMAND ${CMAKE_COMMAND}
                              ${BUILD_OPTION}
                              -G ${CMAKE_GENERATOR}
                              ${NT2_SOURCE_ROOT}/tools/postconfigure
                           && ${CMAKE_COMMAND} --build . --config Release
                      WORKING_DIRECTORY ${NT2_BINARY_DIR}/tools/postconfigure
                     )
    set_property(TARGET postconfigure PROPERTY FOLDER tools)

  endif()

endmacro()

macro(nt2_postconfigure_run)

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
  
  nt2_module_tool(move_reuse ${NT2_BINARY_DIR}/include_tmp ${NT2_BINARY_DIR}/include)

  if(PROJECT_NAME STREQUAL NT2 OR PROJECT_NAME STREQUAL "NT2_${NT2_CURRENT_MODULE_U}")

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
