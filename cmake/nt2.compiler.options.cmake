################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Setup some compliler options
################################################################################
SET( NT2_FLAGS "")

################################################################################
# Fix CMAKE_BUILD_TYPE
################################################################################
IF( NOT CMAKE_BUILD_TYPE )
SET( CMAKE_BUILD_TYPE "Release")
ENDIF()

################################################################################
# Check for special options
################################################################################
INCLUDE(CheckCXXCompilerFlag)
INCLUDE(options/nt2.extra.warnings)

################################################################################
# Add NT2_FLAGS to proper CMAKE_CXX_FLAGS
################################################################################
SET( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${NT2_FLAGS}")
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${NT2_FLAGS}")
SET( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${NT2_FLAGS} -DNT2_DEBUG")
SET( CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${NT2_FLAGS}")
SET( CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} ${NT2_FLAGS}")

################################################################################
# Log current choice
################################################################################
IF( ${CMAKE_BUILD_TYPE} STREQUAL Release )
MESSAGE( STATUS "[NT2] Build type: Release mode (${CMAKE_CXX_FLAGS_RELEASE})" )
SET( NT2_CURRENT_FLAGS ${CMAKE_CXX_FLAGS_RELEASE})
ENDIF()

IF( ${CMAKE_BUILD_TYPE} STREQUAL Debug )
MESSAGE( STATUS "[NT2] Build type: Debug mode (${CMAKE_CXX_FLAGS_DEBUG})" )
SET( NT2_CURRENT_FLAGS ${CMAKE_CXX_FLAGS_DEBUG})
ENDIF()

IF( ${CMAKE_BUILD_TYPE} STREQUAL RelWithDebInfo )
MESSAGE( STATUS "[NT2] Build type: RelWithDebInfo mode (${CMAKE_CXX_FLAGS_RELWITHDEBINFO})" )
SET( NT2_CURRENT_FLAGS ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
ENDIF()

IF( ${CMAKE_BUILD_TYPE} STREQUAL MinSizeRel )
MESSAGE( STATUS "[NT2] Build type: MinSizeRel mode (${CMAKE_CXX_FLAGS_MINSIZEREL})" )
SET( NT2_CURRENT_FLAGS ${CMAKE_CXX_FLAGS_MINSIZEREL})
ENDIF()
