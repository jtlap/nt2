################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

macro(nt2_preprocess target)
  find_file(WAVE_EXECUTABLE wave $ENV{BOOST_ROOT}/dist/bin)
  if(NOT WAVE_EXECUTABLE MATCHES "NOTFOUND$" AND (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX))
    get_directory_property(INCLUDES INCLUDE_DIRECTORIES)
  
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/tmpfile "")
    execute_process(COMMAND ${CMAKE_C_COMPILER} -v -x c++ ${CMAKE_CURRENT_BINARY_DIR}/tmpfile -fsyntax-only
                    ERROR_VARIABLE COMPILER_VERSION_INFO
                   )
    file(REMOVE tmpfile)
                    
    string(REGEX REPLACE "^.*#include <...> search starts here:\n (.*)\nEnd of search list\\..*$" "\\1" INCLUDE_SYSTEM_DIRECTORIES ${COMPILER_VERSION_INFO} )
    string(REPLACE "\n " ";" INCLUDE_SYSTEM_DIRECTORIES ${INCLUDE_SYSTEM_DIRECTORIES} )
    
    foreach(INCLUDE ${INCLUDE_SYSTEM_DIRECTORIES})
      list(APPEND INCLUDE_DIRECTORIES "-S${INCLUDE}")
    endforeach()   
    foreach(INCLUDE ${INCLUDES})
      list(APPEND INCLUDE_DIRECTORIES "-S${INCLUDE}")
    endforeach()
    
    set(prev 0)
    foreach(src ${ARGN})
      math(EXPR n "${prev} + 1")
      add_custom_target(${target}.${n}
                        COMMAND echo "wave ${src}" && ${WAVE_EXECUTABLE} -DNT2_DONT_USE_PREPROCESSED_FILES -DNT2_CREATE_PREPROCESSED_FILES
                        --c++0x --timer
                        ${INCLUDE_DIRECTORIES} -o - ${src}
                        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/include
                       )
      if(prev)
        add_dependencies(${target}.${n} ${target}.${prev}) # we force sequential execution
      endif()
      set(prev ${n})
    endforeach()
    add_custom_target(${target})
    add_dependencies(${target} ${target}.${prev})
    
    # Create target "preprocess" if it doesn't already exist, and make it depend on target
    get_target_property(preprocess_exists preprocess EXCLUDE_FROM_ALL)
    if(preprocess_exists MATCHES "NOTFOUND$")
      add_custom_target(preprocess)
    endif()
    add_dependencies(preprocess ${target})
  endif()
endmacro()
