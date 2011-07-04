##########################################]#####################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Sort out platform info to get a proper BOOST_SIMD_OS value
################################################################################
IF(WIN32)
  SET(BOOST_SIMD_OS "Microsoft Windows")
  SET(BOOST_SIMD_OS_WINDOWS 1)
ELSEIF(APPLE)
  SET(BOOST_SIMD_OS "Mac OS X")
  SET(BOOST_SIMD_OS_MAC_OS 1) 
ELSEIF(UNIX)
  SET(BOOST_SIMD_OS "POSIX")
  SET(BOOST_SIMD_OS_UNIX 1)
ENDIF(WIN32)

################################################################################
# ARM processor
################################################################################
IF(CMAKE_SYSTEM_PROCESSOR MATCHES "arm*")
  SET(BOOST_SIMD_ARCH "ARM")
  SET(BOOST_SIMD_ARCH_ARM 1)
################################################################################
# x86 family processor, 64-bits
################################################################################
ELSEIF(CMAKE_SYSTEM_PROCESSOR MATCHES "amd64*")
  SET(BOOST_SIMD_ARCH "amd64")
  SET(BOOST_SIMD_ARCH_X86 1)
  SET(BOOST_SIMD_ARCH_X86_64 1)
  SET(BOOST_SIMD_ARCH_AMD 1)
  SET(BOOST_SIMD_ARCH_AMD64 1)
ELSEIF(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64*")
  SET(BOOST_SIMD_ARCH "x86_64")
  SET(BOOST_SIMD_ARCH_X86 1)
  SET(BOOST_SIMD_ARCH_X86_64 1)
################################################################################
# x86 family processor
################################################################################
ELSEIF(CMAKE_SYSTEM_PROCESSOR MATCHES "amd*")
  SET(BOOST_SIMD_ARCH "amd")
  SET(BOOST_SIMD_ARCH_X86 1)
  SET(BOOST_SIMD_ARCH_AMD 1)
ELSEIF(  CMAKE_SYSTEM_PROCESSOR MATCHES "i[3-9]86*"
      OR CMAKE_SYSTEM_PROCESSOR MATCHES "x86*"
      )
  SET(BOOST_SIMD_ARCH "x86")
  SET(BOOST_SIMD_ARCH_X86 1)
################################################################################
# Power PC processor
################################################################################
ELSEIF(CMAKE_SYSTEM_PROCESSOR MATCHES "ppc64*")
  SET(BOOST_SIMD_ARCH "PowerPC 64")
  SET(BOOST_SIMD_ARCH_POWERPC 1)
  SET(BOOST_SIMD_ARCH_POWERPC_64 1)
ELSEIF(CMAKE_SYSTEM_PROCESSOR MATCHES "powerpc*")
  SET(BOOST_SIMD_ARCH "PowerPC")
  SET(BOOST_SIMD_ARCH_POWERPC 1)
ENDIF()

IF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  SET(BOOST_SIMD_COMPILER "GCC")
  SET(BOOST_SIMD_COMPILER_GNU_C 1)
ELSEIF(MSVC)
  SET(BOOST_SIMD_COMPILER "Microsoft Visual C++")
  SET(BOOST_SIMD_COMPILER_MSVC 1)
ENDIF()
