################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
set(CTEST_PROJECT_NAME "NT2")
set(CTEST_NIGHTLY_START_TIME "00:00:00 CEST")

set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "cdash.lri.fr")
set(CTEST_DROP_LOCATION "/submit.php?project=NT2")
set(CTEST_DROP_SITE_CDASH TRUE)

set(CTEST_MEMORYCHECK_SUPPRESSIONS_FILE ${CTEST_SOURCE_DIRECTORY}/valgrind.supp)
list(APPEND CTEST_CUSTOM_WARNING_EXCEPTION "You are using gcc version \".*\"")
list(APPEND CTEST_CUSTOM_WARNING_EXCEPTION "[0-9]+ shortened to [0-9]+")

# SITE is host name
execute_process(COMMAND hostname OUTPUT_VARIABLE HOST OUTPUT_STRIP_TRAILING_WHITESPACE)
string(REGEX REPLACE "\\.local$" "" HOST ${HOST})
string(TOLOWER ${HOST} SITE)

# BUILDNAME is generated from OS, architecture, compiler and SIMD level (in-project only)
if(CMAKE_PROJECT_NAME STREQUAL NT2)
  set(OS ${CMAKE_SYSTEM_NAME})
  string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} ARCH)
  if(ARCH MATCHES x86)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
      set(ARCH x86_64)
    else()
      set(ARCH i686)
    endif()
  endif()

  string(TOLOWER ${CMAKE_CXX_COMPILER_ID} COMPILER)
  string(REGEX REPLACE "([0-9]+)\\.([0-9]+).*" "\\1" VERSION_MAJOR "${CMAKE_CXX_COMPILER_VERSION}")
  string(REGEX REPLACE "([0-9]+)\\.([0-9]+).*" "\\2" VERSION_MINOR "${CMAKE_CXX_COMPILER_VERSION}")

  # Compiler version is that of cl.exe, we convert it to MSVC
  if(MSVC AND VERSION_MAJOR)
    math(EXPR VERSION_MAJOR "${VERSION_MAJOR} - 6")
  endif()

  if(VERSION_MINOR)
    set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR})
  else()
    set(VERSION ${VERSION_MAJOR})
  endif()
  set(COMPILER "${COMPILER}${VERSION}")
  if(NOT DEFINED NT2_SIMD_EXT)
    set(OLD_MODULE_PATH ${CMAKE_MODULE_PATH})
    set ( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/modules/boost/simd/sdk/cmake
                            ${PROJECT_SOURCE_DIR}/cmake
        )
    include(nt2.simd)
    set(CMAKE_MODULE_PATH ${OLD_MODULE_PATH})
  endif()

  set(EXT)
  if(NT2_SIMD_EXT)
    set(EXT -${NT2_SIMD_EXT})
  endif()

  set(BUILDNAME "${OS}-${ARCH}${EXT}-${COMPILER}")
  file(WRITE ${PROJECT_BINARY_DIR}/CTestConfigData.cmake "set(BUILDNAME ${BUILDNAME})")

else()
# outside of project, we load a file
  set(PROJECT_SOURCE_DIR ${CTEST_SOURCE_DIRECTORY})
  set(PROJECT_BINARY_DIR ${CTEST_BINARY_DIRECTORY})
  include(${PROJECT_BINARY_DIR}/CTestConfigData.cmake)
endif()

# We add branch tag if necessary
find_package(Git QUIET)
if(GIT_EXECUTABLE)
  execute_process(COMMAND ${GIT_EXECUTABLE} symbolic-ref HEAD
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                  OUTPUT_VARIABLE BRANCH OUTPUT_STRIP_TRAILING_WHITESPACE
                  RESULT_VARIABLE BRANCH_RESULT ERROR_QUIET
                 )
  if(NOT BRANCH_RESULT)
   string(REGEX REPLACE "^.+/([^/]+)$" "\\1" BRANCH ${BRANCH})
  else()
    set(BRANCH "dirty")
  endif()

  if(NOT BRANCH STREQUAL "master")
    set(BUILDNAME "${BUILDNAME}-${BRANCH}")
  endif()
endif()

set(CTEST_SITE ${SITE})
set(CTEST_BUILD_NAME ${BUILDNAME})
