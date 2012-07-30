################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

set(NT2_WITH_PCH 1 CACHE BOOL "Whether to use precompiled headers on platforms that support it")

macro(nt2_pch name)
  if(NT2_PCH_TARGET)
    message(FATAL_ERROR "[nt2.pch] precompiled header already set to ${NT2_PCH_TARGET}, cannot change to ${name}")
  endif()

  if((CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) AND CMAKE_GENERATOR MATCHES "Make")

    get_target_property(pch_exists pch EXCLUDE_FROM_ALL)
    if(pch_exists MATCHES "NOTFOUND$")
      add_custom_target(pch ALL)
    endif()

    foreach(BUILD_TYPE Debug Release NT2Test NT2TestDebug NT2Bench)
      string(TOUPPER ${BUILD_TYPE} BUILD_TYPE_U)
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

      set(name_ "${name}/${BUILD_TYPE}")
      string(REPLACE "/" "_" pch_base ${name})
      string(REPLACE "/" "_" pch_base_ ${name_})
      string(REGEX REPLACE "\\.hpp$" "" rule ${pch_base})
      string(REGEX REPLACE "\\.hpp$" "_${BUILD_TYPE}" rule_ ${pch_base})
      file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${pch_base_} "#include <${name}>\n")
      add_custom_command(OUTPUT ${pch_base_}.gch
                         COMMAND ${CMAKE_CXX_COMPILER} ${FLAGS} ${INCLUDES} -x c++-header -c ${file} -o ${pch_base_}.gch
                         IMPLICIT_DEPENDS CXX ${file}
                         COMMENT "Precompiling header file ${name} for configuration ${BUILD_TYPE}..."
                        )
      add_custom_target(${rule_}.pch
                        DEPENDS ${pch_base_}.gch
                       )
      add_dependencies(pch ${rule_}.pch)
      set(NT2_PCH_TARGET ${rule})
      # Escape special characters. Unfortunately CMake doesn't already take care of it when using add_definitionss
      string(REGEX REPLACE "([ \\\\\"&|;#])" "\\\\\\1" path "${CMAKE_CURRENT_BINARY_DIR}/${pch_base_}")
      set(CMAKE_CXX_FLAGS_${BUILD_TYPE_U} "${CMAKE_CXX_FLAGS_${BUILD_TYPE_U}} -include ${path} -Winvalid-pch")
    endforeach()
  endif()
endmacro()
