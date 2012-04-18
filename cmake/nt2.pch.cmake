################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

macro(nt2_pch name)
  if((CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) AND NOT CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE_U)
    set(FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${BUILD_TYPE_U}}")
    string(REPLACE " " ";" FLAGS ${FLAGS})

    get_directory_property(COMPILE_DEFINITIONS COMPILE_DEFINITIONS)
    foreach(DEFINITION ${COMPILE_DEFINITIONS})
      list(APPEND ${FLAGS} -D${DEFINITION})
    endforeach()

    get_directory_property(INCLUDE_DIRECTORIES INCLUDE_DIRECTORIES)
    set(INCLUDES)
    foreach(INCLUDE ${INCLUDE_DIRECTORIES})
      list(APPEND INCLUDES "-I${INCLUDE}")
      if(EXISTS ${INCLUDE}/${name})
        set(file ${INCLUDE}/${name})
      endif()
    endforeach()

    string(REPLACE "/" "_" pch_base ${name})
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${pch_base} "#error this file has not been precompiled, make the ${pch_base}.pch target")
    add_custom_target(${pch_base}.pch
                      COMMAND ${CMAKE_CXX_COMPILER} ${FLAGS} ${INCLUDES} -x c++-header -c ${file} -o ${pch_base}.gch
                      DEPENDS ${file}
                      COMMENT "Precompiling header file ${name}..."
                     )
    add_definitions(-include ${CMAKE_CURRENT_BINARY_DIR}/${pch_base} -Winvalid-pch)
  endif()
endmacro()
