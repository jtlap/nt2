##########################################]#####################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Sort out platform info to get a proper NT2_PLATFORM value
################################################################################
IF(WIN32)
SET( NT2_PLATFORM_WIN32 "Microsoft Windows")
ELSEIF(APPLE)
SET( NT2_PLATFORM_OSX "Mac OS X")
ELSEIF(UNIX)
SET( NT2_PLATFORM_UNIX "Unix")
ENDIF(WIN32)

################################################################################
# ARM processor
################################################################################
IF(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm*")
SET( NT2_PROCESSOR "ARM")
SET( NT2_ARM_PROCESSOR 1)
################################################################################
# x86 family processor, 64-bits
################################################################################
ELSEIF(  ${CMAKE_SYSTEM_PROCESSOR} MATCHES "amd64*"
		  OR ${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64*"
      )
SET( NT2_PROCESSOR "x86_64")
SET( NT2_X86_PROCESSOR 1)
################################################################################
# x86 family processor
################################################################################
ELSEIF(  ${CMAKE_SYSTEM_PROCESSOR} MATCHES "i[3-9]86*"
      OR ${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86*"
      OR ${CMAKE_SYSTEM_PROCESSOR} MATCHES "amd*"
      )
SET( NT2_PROCESSOR "x86")
SET( NT2_X86_PROCESSOR 1)
################################################################################
# Power PC processor
################################################################################
ELSEIF(   ${CMAKE_SYSTEM_PROCESSOR} MATCHES "ppc64*"
      OR  ${CMAKE_SYSTEM_PROCESSOR} MATCHES "powerpc*"
      )
SET( NT2_PROCESSOR "PowerPC")
SET( NT2_PPC_PROCESSOR 1)
ENDIF(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm*")
