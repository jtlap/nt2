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

MESSAGE( STATUS "[nt2] target system: ${NT2_OS} (${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION})" )
MESSAGE( STATUS "[nt2] target processor: ${NT2_ARCH}" )

SET(NT2_CONFIG_DEPENDENCIES_FOUND 1)
SET(NT2_CONFIG_DEPENDENCIES_INCLUDE_DIR ${Boost_INCLUDE_DIRS})
SET(NT2_CONFIG_DEPENDENCIES_LIBRARY_DIR ${Boost_LIBRARY_DIRS})
SET(NT2_CONFIG_DEPENDENCIES_EXTRA extension)

SET(NT2_CONFIG_FLAGS ${NT2_CXX_SIMD_FLAGS})
