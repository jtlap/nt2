################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Add the target to build filter and postprocess
################################################################################
FIND_FILE(PROFILER_PATH profiler ${CMAKE_MODULE_PATH})

MESSAGE(STATUS "PROFILER: ${CMAKE_BINARY_DIR}")

ADD_EXECUTABLE(template.profiler.filter ${PROFILER_PATH}/filter.cpp)
set_property(TARGET template.profiler.filter PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tools)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
ADD_EXECUTABLE(template.profiler.postprocess ${PROFILER_PATH}/postprocess.cpp)
target_link_libraries(template.profiler.postprocess ${Boost_LIBRARIES})
set_property(TARGET template.profiler.postprocess PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tools)

################################################################################
# Make a macro to compile foo and profile it
################################################################################
macro(template_profile target src)
  get_directory_property(INCLUDES INCLUDE_DIRECTORIES)
  foreach(INCLUDE ${INCLUDES})
    list(APPEND INCLUDE_DIRECTORIES -I${INCLUDE})
  endforeach()

  add_custom_command(OUTPUT ${target}.preprocessed.cpp
                     COMMAND ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}} ${INCLUDE_DIRECTORIES} -E ${CMAKE_CURRENT_SOURCE_DIR}/${src}
                           | ${PERL_EXECUTABLE} ${PROFILER_PATH}/preprocess.pl > ${target}.preprocessed.cpp
                     DEPENDS ${src}
                   )
  add_custom_command(OUTPUT ${target}.template_profile
                     COMMAND ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}} -I${PROFILER_PATH} -c -DPROFILE_TEMPLATES ${target}.preprocessed.cpp 2>&1
                           | ${CMAKE_BINARY_DIR}/tools/template.profiler.filter ${ARGN} > ${target}.filtered && ${CMAKE_BINARY_DIR}/tools/template.profiler.postprocess  --call-graph ${ARGN} ${target}.filtered > ${target}.template_profile
                     DEPENDS ${target}.preprocessed.cpp
                             template.profiler.filter
                             template.profiler.postprocess
                    )
  add_custom_target (${target}
                     DEPENDS ${target}.template_profile
                    )
endmacro()
