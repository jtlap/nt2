################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
cmake_minimum_required(VERSION 2.6)

# We link statically with MSVC
if(MSVC)
  foreach(flag_var CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
                   CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    string(REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
  endforeach()
endif()  
  
set(Boost_ADDITIONAL_VERSIONS "1.46" "1.46.0" "1.46.1" "1.47" "1.47.0" "1.48" "1.48.0")
find_package(Boost 1.46.0 REQUIRED)
if(Boost_VERSION LESS 104600)
  message(FATAL_ERROR "Boost version ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION} not recent enough, needs 1.46.0")
endif()

include_directories(${CMAKE_SOURCE_DIR}/../gather_includes ${Boost_INCLUDE_DIRS})

add_executable(postconfigure postconfigure.cpp)
set_target_properties(postconfigure
                      PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}
                     )

# Request administrator rights to run this executable
if(0) #MSVC)
  set_target_properties(postconfigure
                        PROPERTIES LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\""
                       )
endif()
