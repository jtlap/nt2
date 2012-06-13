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

if(CMAKE_PROJECT_NAME STREQUAL NT2 AND UNIX AND NOT CMAKE_CROSSCOMPILING)
  execute_process(COMMAND hostname OUTPUT_VARIABLE HOST OUTPUT_STRIP_TRAILING_WHITESPACE)
  string(REGEX REPLACE "\\.local$" "" HOST ${HOST})
  set(SITE ${HOST})

  execute_process(COMMAND uname -s OUTPUT_VARIABLE OS OUTPUT_STRIP_TRAILING_WHITESPACE)
  execute_process(COMMAND uname -m OUTPUT_VARIABLE ARCH OUTPUT_STRIP_TRAILING_WHITESPACE)

  if(CMAKE_COMPILER_IS_GNUCC)
    set(COMPILER gcc)
  else()
    get_filename_component(COMPILER ${CMAKE_C_COMPILER} NAME_WE)
  endif()
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
                  OUTPUT_VARIABLE COMPILER_VERSION
                  RESULT_VARIABLE COMPILER_VERSION_ERR
                  ERROR_QUIET
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  if(NOT COMPILER_VERSION_ERR)
    set(COMPILER "${COMPILER}${COMPILER_VERSION}")
  endif()

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
    set(EXT -${NT2_SIMD_EXT}-)
  endif()

  set(BUILDNAME "${OS}-${ARCH}${EXT}${COMPILER}")

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

endif()
