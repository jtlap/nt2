################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Display Architecture info
################################################################################
MESSAGE( STATUS "[NT2] Target processor : ${CMAKE_SYSTEM_PROCESSOR}" )
MESSAGE( STATUS "[NT2] Target system    : ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION}" )

################################################################################
# Sort out platform info to get a proper NT2_PLATFORM value
################################################################################
IF(WIN32)
SET( NT2_PLATFORM_WIN32 "Microsoft Windows")
ELSEIF(APPLE)
SET( NT2_PLATFORM_OSX "Mac OS X")
ELSEIF(UNIX)
SET( NT2_PLATFORM_UNIX "Unix")
ENDIF()

IF(NT2_PLATFORM_WIN32)
MESSAGE( STATUS "[NT2] Target system    : ${NT2_PLATFORM_WIN32N}" )
ENDIF()

IF(NT2_PLATFORM_OSX)
MESSAGE( STATUS "[NT2] Target system    : ${NT2_PLATFORM_OSX}" )
ENDIF()

IF(NT2_PLATFORM_UNIX)
MESSAGE( STATUS "[NT2] Target system    : ${NT2_PLATFORM_UNIX}" )
ENDIF()
