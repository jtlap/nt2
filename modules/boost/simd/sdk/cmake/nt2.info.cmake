##########################################]#####################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Sort out platform info to get a proper NT2_OS value
################################################################################
IF(WIN32)
  SET(NT2_OS "Microsoft Windows")
  SET(NT2_OS_WINDOWS 1)
ELSEIF(APPLE)
  SET(NT2_OS "Mac OS X")
  SET(NT2_OS_MAC_OS 1) 
ELSEIF(UNIX)
  SET(NT2_OS "POSIX")
  SET(NT2_OS_UNIX 1)
ENDIF(WIN32)

################################################################################
# ARM processor
################################################################################
IF(CMAKE_SYSTEM_PROCESSOR MATCHES "arm*")
  SET(NT2_ARCH "ARM")
  SET(NT2_ARCH_ARM 1)
################################################################################
# x86 family processor, 64-bits
################################################################################
ELSEIF(CMAKE_SYSTEM_PROCESSOR MATCHES "amd64*")
  SET(NT2_ARCH "amd64")
  SET(NT2_ARCH_X86 1)
  SET(NT2_ARCH_X86_64 1)
  SET(NT2_ARCH_AMD 1)
  SET(NT2_ARCH_AMD64 1)
ELSEIF(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64*")
  SET(NT2_ARCH "x86_64")
  SET(NT2_ARCH_X86 1)
  SET(NT2_ARCH_X86_64 1)
################################################################################
# x86 family processor
################################################################################
ELSEIF(CMAKE_SYSTEM_PROCESSOR MATCHES "amd*")
  SET(NT2_ARCH "amd")
  SET(NT2_ARCH_X86 1)
  SET(NT2_ARCH_AMD 1)
ELSEIF(  CMAKE_SYSTEM_PROCESSOR MATCHES "i[3-9]86*"
      OR CMAKE_SYSTEM_PROCESSOR MATCHES "x86*"
      )
  SET(NT2_ARCH "x86")
  SET(NT2_ARCH_X86 1)
################################################################################
# Power PC processor
################################################################################
ELSEIF(CMAKE_SYSTEM_PROCESSOR MATCHES "ppc64*")
  SET(NT2_ARCH "PowerPC 64")
  SET(NT2_ARCH_POWERPC 1)
  SET(NT2_ARCH_POWERPC_64 1)
ELSEIF(CMAKE_SYSTEM_PROCESSOR MATCHES "powerpc*")
  SET(NT2_ARCH "PowerPC")
  SET(NT2_ARCH_POWERPC 1)
ENDIF()

IF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  SET(NT2_COMPILER "GCC")
  SET(NT2_COMPILER_GCC 1)
ELSEIF(MSVC)
  SET(NT2_COMPILER "Microsoft Visual C++")
  SET(NT2_COMPILER_MSVC 1)
ENDIF()