################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(nt2.boost)
IF(NOT Boost_FOUND)
  SET(NT2_CONFIG_DEPENDENCIES_FOUND 0)
  RETURN()
ENDIF()

include(nt2.simd)

IF(NT2_PLATFORM_WIN32)
MESSAGE( STATUS "[nt2] target system: ${NT2_PLATFORM_WIN32} (${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION})" )
ENDIF(NT2_PLATFORM_WIN32)

IF(NT2_PLATFORM_OSX)
MESSAGE( STATUS "[nt2] target system: ${NT2_PLATFORM_OSX} (${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION})" )
ENDIF(NT2_PLATFORM_OSX)

IF(NT2_PLATFORM_UNIX)
MESSAGE( STATUS "[nt2] target system: ${NT2_PLATFORM_UNIX} (${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION})" )
ENDIF(NT2_PLATFORM_UNIX)

MESSAGE( STATUS "[nt2] target processor: ${NT2_PROCESSOR}" )

SET(NT2_CONFIG_DEPENDENCIES_FOUND 1)
SET(NT2_CONFIG_DEPENDENCIES_INCLUDE_DIR ${Boost_INCLUDE_DIRS})
SET(NT2_CONFIG_DEPENDENCIES_LIBRARY_DIR ${Boost_LIBRARY_DIRS})
SET(NT2_CONFIG_DEPENDENCIES_EXTRA extension)

SET(NT2_CONFIG_FLAGS ${NT2_CXX_SIMD_FLAGS})
