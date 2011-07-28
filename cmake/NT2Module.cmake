################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

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
  set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
  
  include_directories(${NT2_${NT2_CURRENT_MODULE_U}_INCLUDE_DIR})
  link_directories(${NT2_${NT2_CURRENT_MODULE_U}_DEPENDENCIES_LIBRARY_DIR})
  link_libraries(${NT2_${NT2_CURRENT_MODULE_U}_DEPENDENCIES_LIBRARIES})
  set(NT2_CURRENT_FLAGS "${NT2_CURRENT_FLAGS} ${NT2_${NT2_CURRENT_MODULE_U}_FLAGS}")
  
  # installation is only done when current project is NT2
  # or same as current module
  if(PROJECT_NAME STREQUAL NT2 OR PROJECT_NAME STREQUAL "NT2_${NT2_CURRENT_MODULE_U}")

    nt2_module_install_setup()

    # set up component
    if(CPACK_GENERATOR)
      cpack_add_component(${module}
                          DEPENDS ${NT2_${NT2_CURRENT_MODULE_U}_DEPENDENCIES_EXTRA}
                         )
    endif()
  
    # install headers, cmake modules and manifest
    install( DIRECTORY ${NT2_${NT2_CURRENT_MODULE_U}_ROOT}/include/
             DESTINATION include
             COMPONENT ${module}
             FILES_MATCHING PATTERN "*.hpp"
           )
    file(WRITE ${PROJECT_BINARY_DIR}/modules/${module}.manifest)
    install( FILES ${PROJECT_BINARY_DIR}/modules/${module}.manifest
             DESTINATION ${NT2_INSTALL_SHARE_DIR}/modules
             COMPONENT ${module}
           )
    install( DIRECTORY ${NT2_${NT2_CURRENT_MODULE_U}_ROOT}/cmake
             DESTINATION ${NT2_INSTALL_SHARE_DIR}
             COMPONENT ${module}
             FILES_MATCHING PATTERN "*.cmake"
           )
  endif()
  
endmacro()

macro(nt2_setup_variant)
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
  elseif(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DNT2_DEBUG")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DNT2_DEBUG")
  endif()
endmacro()

macro(nt2_module_dir dir)
  if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${dir})
      get_target_property(${dir}_exists ${dir} EXCLUDE_FROM_ALL)
      if(${dir}_exists MATCHES "NOTFOUND$")
        add_custom_target(${dir})
      endif()
      add_custom_target(${NT2_CURRENT_MODULE}.${dir})
      add_dependencies(${dir} ${NT2_CURRENT_MODULE}.${dir})
      add_subdirectory(${dir})
    endif()
endmacro()

macro(nt2_module_main module)
  string(TOUPPER ${module} NT2_CURRENT_MODULE_U)
    
  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL ${PROJECT_SOURCE_DIR})
    project(NT2_${NT2_CURRENT_MODULE_U})
    include(CPack)
  endif()

  nt2_setup_variant()
  
  set(NT2_CURRENT_MODULE ${module})
  nt2_module_use_modules(${module})
  
  if(CMAKE_GENERATOR MATCHES "Make")
    set(NT2_WITH_TESTS_ 1)
  else()
    set(NT2_WITH_TESTS_ 0)
  endif()
  option(NT2_WITH_TESTS "Enable benchmarks and unit tests" ${NT2_WITH_TESTS_})
  option(NT2_WITH_TESTS_COVER "Enable cover tests" OFF)
  
  if(NT2_WITH_TESTS_COVER AND NOT NT2_WITH_TESTS)
    set(NT2_WITH_TESTS 1 CACHE BOOL "Enable benchmarks and unit tests" FORCE)
  endif()

  if(NT2_WITH_TESTS)
    ENABLE_TESTING()
    
    nt2_module_dir(bench)
    nt2_module_dir(examples)
    nt2_module_dir(unit)
    
    if(NT2_WITH_TESTS_COVER)
      nt2_module_dir(cover)
    endif()
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
      set(NT2_${NT2_CURRENT_MODULE_U}_DYN_LINK 1)
    else()
      add_library(${libname} STATIC ${ARGN})
    endif()
  else()
    add_library(${libname} ${ARGN})
    set(NT2_${NT2_CURRENT_MODULE_U}_DYN_LINK ${BUILD_SHARED_LIBS})
  endif()

  set_target_properties(${libname} PROPERTIES VERSION 3.0.0 SOVERSION 3)
  
  set(FLAGS "${NT2_CURRENT_FLAGS} -DNT2_${NT2_CURRENT_MODULE_U}_SOURCE")
  if(NT2_${NT2_CURRENT_MODULE_U}_DYN_LINK)
    set(FLAGS "${FLAGS} -DNT2_${NT2_CURRENT_MODULE_U}_DYN_LINK")
  endif()
  set_property(TARGET ${libname} PROPERTY COMPILE_FLAGS ${FLAGS})
  
  if(PROJECT_NAME STREQUAL NT2 OR PROJECT_NAME STREQUAL "NT2_${NT2_CURRENT_MODULE_U}")
    install( TARGETS ${libname}
             LIBRARY DESTINATION lib
             ARCHIVE DESTINATION lib
             COMPONENT ${NT2_CURRENT_MODULE}
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
    nt2_find_transfer_parent()
    return()
  endif()

  include_directories(${NT2_INCLUDE_DIR})
  link_directories(${NT2_LIBRARY_DIR})
  link_libraries(${NT2_LIBRARIES})
  
  set(NT2_CURRENT_FLAGS "${NT2_CURRENT_FLAGS} ${NT2_FLAGS}")
  
  nt2_find_transfer_parent()
endmacro()

macro(nt2_module_add_exe DIRECTORY EXECUTABLE)
  string(TOUPPER ${NT2_CURRENT_MODULE} NT2_CURRENT_MODULE_U)

  add_executable(${EXECUTABLE} EXCLUDE_FROM_ALL ${ARGN})
  
  set_property(TARGET ${EXECUTABLE} PROPERTY COMPILE_FLAGS ${NT2_CURRENT_FLAGS})
  set_property(TARGET ${EXECUTABLE} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${DIRECTORY})
endmacro()

macro(nt2_module_add_test DIRECTORY EXECUTABLE)
  nt2_module_add_exe(${DIRECTORY} ${EXECUTABLE} ${ARGN})

  string(REGEX REPLACE "\\.([^.]+)\\.${DIRECTORY}$" ".${DIRECTORY}" suite ${EXECUTABLE})
  string(REGEX REPLACE "\\.${DIRECTORY}$" "-${DIRECTORY}" TEST ${EXECUTABLE})
  
  add_dependencies(${suite} ${EXECUTABLE})
  if(NOT CMAKE_CROSSCOMPILING_HOST AND DEFINED ENV{CMAKE_CROSSCOMPILING_HOST})
    set(CMAKE_CROSSCOMPILING_HOST $ENV{CMAKE_CROSSCOMPILING_HOST})
  endif()
  if(CMAKE_CROSSCOMPILING AND CMAKE_CROSSCOMPILING_HOST)
    add_test(${TEST} /bin/sh -c "scp ${PROJECT_BINARY_DIR}/${DIRECTORY}/${EXECUTABLE} ${CMAKE_CROSSCOMPILING_HOST}:/tmp && ssh ${CMAKE_CROSSCOMPILING_HOST} /tmp/${EXECUTABLE} && ssh ${CMAKE_CROSSCOMPILING_HOST} rm /tmp/${EXECUTABLE}")
  else()
    add_test(${TEST} ${PROJECT_BINARY_DIR}/${DIRECTORY}/${EXECUTABLE})
  endif()
endmacro()

macro(nt2_module_add_unit)
  nt2_module_add_test(unit ${ARGN})
endmacro()

macro(nt2_module_add_cover)
  nt2_module_add_test(cover ${ARGN})
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

macro(nt2_module_install_file header)
  string(TOUPPER ${NT2_CURRENT_MODULE} NT2_CURRENT_MODULE_U)

  if(PROJECT_NAME STREQUAL NT2 OR PROJECT_NAME STREQUAL "NT2_${NT2_CURRENT_MODULE_U}")
    string(REGEX REPLACE "^(.*)/[^/]+$" "\\1" ${header}_path ${header})
    install(FILES ${PROJECT_BINARY_DIR}/include/${header}
            DESTINATION include/${${header}_path}
            COMPONENT ${NT2_CURRENT_MODULE}
           )
  endif()
endmacro()

macro(nt2_module_configure_py pyfile)
  string(TOUPPER ${NT2_CURRENT_MODULE} NT2_CURRENT_MODULE_U)

  if(NOT PYTHON_EXECUTABLE)
    find_package(PythonInterp QUIET)
    if(NOT PYTHONINTERP_FOUND)
      set(NT2_ARITHMETIC_DEPENDENCIES_FOUND 0)
      message(FATAL_ERROR "Python is necessary to configure sources of module ${NT2_CURRENT_MODULE}")
    endif()
  endif()

  find_file(_${pyfile}_PY ${pyfile} ${CMAKE_MODULE_PATH} NO_DEFAULT_PATH)
  set(_${pyfile}_PY ${_${pyfile}_PY} CACHE INTERNAL "" FORCE)
  execute_process( COMMAND ${PYTHON_EXECUTABLE}
                   ${_${pyfile}_PY} --display
                   ${NT2_${NT2_CURRENT_MODULE_U}_ROOT}/include ${PROJECT_BINARY_DIR}/include
                   ${ARGN}
                   OUTPUT_VARIABLE ${pyfile}_result
                   OUTPUT_STRIP_TRAILING_WHITESPACE
                 )
   
  if(PROJECT_NAME STREQUAL NT2 OR PROJECT_NAME STREQUAL "NT2_${NT2_CURRENT_MODULE_U}" AND ${pyfile}_result)
    string(REPLACE "\n" ";" ${pyfile}_files ${${pyfile}_result})
    foreach(gen_file ${${pyfile}_files})
      nt2_module_install_file(${gen_file})
    endforeach()
  endif()
endmacro()

macro(nt2_module_configure_simd)
  nt2_module_configure_py(simd_fwd.py ${ARGN})
endmacro()

macro(nt2_module_configure_include)
  nt2_module_configure_py(include_fwd.py ${ARGN})
endmacro()

macro(nt2_module_configure_toolbox toolbox is_sys)
  if(${is_sys})
    nt2_module_configure_include(nt2/toolbox/${toolbox}/function -o nt2/toolbox/${toolbox}/include -o nt2/include/functions)
    nt2_module_configure_simd(nt2/toolbox/${toolbox}/function)
  else()
    nt2_module_configure_include(nt2/toolbox/${toolbox}/function -o nt2/toolbox/${toolbox}/include)
  endif()
endmacro()

macro(nt2_module_configure_file cmake_file header)
  configure_file(${cmake_file} ${PROJECT_BINARY_DIR}/include/${header})
  nt2_module_install_file(${header})
endmacro()

macro(nt2_module_simd_toolbox name)
  string(TOUPPER ${name} name_U)
  get_directory_property(INCLUDE_DIRECTORIES INCLUDE_DIRECTORIES)
  foreach(dir ${INCLUDE_DIRECTORIES})
    file(GLOB function_files RELATIVE ${dir}/boost/simd/toolbox/${name}/function ${dir}/boost/simd/toolbox/${name}/function/*.hpp)
    foreach(file ${function_files})
      string(REGEX REPLACE ".hpp" "" file ${file})
      string(TOUPPER ${file} file_U)
      file(WRITE ${PROJECT_BINARY_DIR}/include/nt2/toolbox/${name}/include/${file}.hpp
                "#ifndef NT2_TOOLBOX_${name_U}_INCLUDE_${file_U}_HPP_INCLUDED\n"
                "#define NT2_TOOLBOX_${name_U}_INCLUDE_${file_U}_HPP_INCLUDED\n"
                "#include <boost/simd/toolbox/${name}/function/${file}.hpp>\n"
                "namespace nt2\n"
                "{\n"
                "  namespace tag\n"
                "  {\n"
                "    using boost::simd::tag::${file}_;\n"
                "  }\n"
                "  using boost::simd::${file};\n"
                "}\n"
                "#endif\n"
          )
    endforeach()
    
    file(GLOB constant_files RELATIVE ${dir}/boost/simd/toolbox/${name}/constants ${dir}/boost/simd/toolbox/${name}/constants/*.hpp)
    foreach(file ${constant_files})
      string(REGEX REPLACE ".hpp" "" file ${file})
      string(TOUPPER ${file} file_U)
      file(WRITE ${PROJECT_BINARY_DIR}/include/nt2/toolbox/${name}/include/${file}.hpp
                "#ifndef NT2_TOOLBOX_${name_U}_INCLUDE_${file_U}_HPP_INCLUDED\n"
                "#define NT2_TOOLBOX_${name_U}_INCLUDE_${file_U}_HPP_INCLUDED\n"
                "#include <nt2/toolbox/${name}/${name}.hpp>\n" # Workaround
                "#endif\n"
          )
    endforeach()
    
    file(GLOB include_files RELATIVE ${dir}/boost/simd/toolbox/${name}/include ${dir}/boost/simd/toolbox/${name}/include/*.hpp)
    foreach(file ${include_files})
      file(READ ${dir}/boost/simd/toolbox/${name}/include/${file} file_content)
      string(REPLACE "boost/simd/" "nt2/" file_content ${file_content})
      string(REPLACE "BOOST_SIMD_" "NT2_" file_content ${file_content})
      file(WRITE ${PROJECT_BINARY_DIR}/include/nt2/toolbox/${name}/include/${file} ${file_content})
    endforeach()
  endforeach()
    
  if(${name} STREQUAL constant)
    nt2_module_configure_include(nt2/toolbox/${name}/include -o nt2/include/constants)
  else()
    nt2_module_configure_include(nt2/toolbox/${name}/include -o nt2/include/functions)
  endif()
endmacro()
