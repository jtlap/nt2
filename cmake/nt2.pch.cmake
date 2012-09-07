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

  if(NT2_WITH_PCH AND (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang") AND CMAKE_GENERATOR MATCHES "Make|Ninja")

    get_target_property(pch_exists pch EXCLUDE_FROM_ALL)
    if(pch_exists MATCHES "NOTFOUND$")
      add_custom_target(pch ALL)
    endif()

    foreach(BUILD_TYPE Debug Release NT2Test NT2TestDebug NT2Bench)
      string(TOUPPER ${BUILD_TYPE} BUILD_TYPE_U)
      set(name_ "${name}/${BUILD_TYPE}")
      string(REPLACE "/" "_" pch_base ${name})
      string(REPLACE "/" "_" pch_base_ ${name_})
      string(REGEX REPLACE "\\.hpp$" "" rule ${pch_base})
      string(REGEX REPLACE "\\.hpp$" "_${BUILD_TYPE}" rule_ ${pch_base})

      file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${pch_base_} "#include <${name}>\n")
      set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/${pch_base_} PROPERTIES LANGUAGE CXX)

      set(object_suffix .o)
      if(WIN32)
        set(object_suffix .obj)
      endif()

      add_library(${rule_}.pch STATIC ${CMAKE_CURRENT_BINARY_DIR}/${pch_base_})
      set_target_properties(${rule_}.pch PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS_${BUILD_TYPE_U}} -x c++-header")
      add_custom_command(TARGET ${rule_}.pch POST_BUILD
                         COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${rule_}.pch.dir/${pch_base_}${object_suffix}
                                                          ${CMAKE_CURRENT_BINARY_DIR}/${pch_base_}.gch
                         COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${rule_}.pch.dir/${pch_base_}${object_suffix}
                         COMMAND ${CMAKE_COMMAND} -E touch  ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${rule_}.pch.dir/${pch_base_}${object_suffix}
                         COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${rule_}.pch${CMAKE_STATIC_LIBRARY_SUFFIX}
                         COMMAND ${CMAKE_COMMAND} -E touch  ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${rule_}.pch${CMAKE_STATIC_LIBRARY_SUFFIX}
                        )
      add_dependencies(pch ${rule_}.pch)
      set(NT2_PCH_TARGET ${rule})
      # Escape special characters
      string(REGEX REPLACE "([ \\\\\"&|;#])" "\\\\\\1" path "${CMAKE_CURRENT_BINARY_DIR}/${pch_base_}")
      set(CMAKE_CXX_FLAGS_${BUILD_TYPE_U} "${CMAKE_CXX_FLAGS_${BUILD_TYPE_U}} -include ${path} -Winvalid-pch")
    endforeach()
  endif()
endmacro()
