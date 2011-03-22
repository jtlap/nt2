################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

# A function is necessary for recursive invocations of the find script
function(nt2_find COMPONENT)

  string(TOUPPER ${COMPONENT} COMPONENT_U)
  
  if(${NT2_${COMPONENT_U}_FOUND})
    return()
  endif()
  
  # Search for installation
  # TODO
  
  # Search for source
  if(DEFINED ENV{NT2_${COMPONENT_U}_ROOT})
    set(NT2_${COMPONENT_U}_ROOT $ENV{NT2_${COMPONENT_U}_ROOT})
  elseif(DEFINED NT2_MODULAR_ROOT)
    set(NT2_${COMPONENT_U}_ROOT "${NT2_MODULAR_ROOT}/modules/${COMPONENT}")
  endif()
    
  if(DEFINED NT2_${COMPONENT_U}_ROOT)
    message(STATUS "[NT2] Found ${COMPONENT} module source, setting dependencies")
    
    set(CMAKE_MODULE_PATH "${NT2_${COMPONENT_U}_ROOT}/cmake" ${CMAKE_MODULE_PATH})
    find_file(NT2_${COMPONENT_U}_DEPENDENCIES_FILE "nt2.${COMPONENT}.dependencies.cmake" ${CMAKE_MODULE_PATH})
    IF(NOT ${NT2_${COMPONENT_U}_DEPENDENCIES_FILE} MATCHES "NOTFOUND")
      include(${NT2_${COMPONENT_U}_DEPENDENCIES_FILE})
    ENDIF()
    
    set(NT2_${COMPONENT_U}_INCLUDE_DIR ${NT2_${COMPONENT_U}_DEPENDENCIES_INCLUDE_DIR} "${NT2_${COMPONENT_U}_ROOT}/include" PARENT_SCOPE)
    
  else()
    message(STATUS "[NT2] Module ${COMPONENT} not found")
    set(NT2_FOUND 0 PARENT_SCOPE)
    
  endif()
  
  set(NT2_${COMPONENT_U}_FOUND ${NT2_FOUND} PARENT_SCOPE)
  
endfunction()

set(NT2_FOUND 1)

if(DEFINED ENV{NT2_MODULAR_ROOT})
  message(STATUS "[NT2] Found modular root")
  set(NT2_MODULAR_ROOT $ENV{NT2_MODULAR_ROOT})
endif()

foreach(COMPONENT ${NT2_FIND_COMPONENTS})
  nt2_find(${COMPONENT})
endforeach()
