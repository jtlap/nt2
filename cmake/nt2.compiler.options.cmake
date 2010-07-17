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
include(CheckCXXCompilerFlag)

################################################################################
# g++ command line
################################################################################
IF(CMAKE_COMPILER_IS_GNUCXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_THREAD_LIBS_INIT}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

################################################################################
# Configuration options
################################################################################
IF(MMX_FOUND)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmmx")
ENDIF(MMX_FOUND)

IF(SSE2_FOUND)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2")
ENDIF(SSE2_FOUND)

IF(SSE3_FOUND)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse3")
ENDIF(SSE3_FOUND)

IF(SSSE3_FOUND)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mssse3")
ENDIF(SSSE3_FOUND)

IF(SSE4_1_FOUND)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4_1")
ENDIF(SSE4_1_FOUND)

IF(SSE4_2_FOUND)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4_2")
ENDIF(SSE4_2_FOUND)

IF(SSE4A_FOUND)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4a")
ENDIF(SSE4A_FOUND)

IF(AVX_FOUND)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx")
ENDIF(AVX_FOUND)

IF(ALTIVEC_FOUND)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maltivec")
ENDIF(ALTIVEC_FOUND)

MESSAGE(STATUS "Compiling NT2 with" ${CMAKE_CXX_FLAGS})

################################################################################
# User Options
################################################################################

################################################################################
# Build as static library
################################################################################

################################################################################
# Add -Wextra
################################################################################
OPTION(NT2_EXTRA_WARNINGS "Enable/Disable extra warnings" OFF)
IF(NT2_EXTRA_WARNINGS)
check_cxx_compiler_flag("-Wextra" HAS_WEXTRA)
IF(HAS_WEXTRA)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
message(STATUS "Enabling extra warnings")
ENDIF(HAS_WEXTRA)
ENDIF(NT2_EXTRA_WARNINGS)

################################################################################
# Add -pedantic
################################################################################
OPTION(NT2_PEDANTIC "Enable/Disable pedantic compilation" OFF)
IF(NT2_PEDANTIC)
check_cxx_compiler_flag("-pedantic" HAS_PEDANTIC)
IF(HAS_PEDANTIC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
message(STATUS "Enabling pedantic compilation")
ENDIF(HAS_PEDANTIC)
ENDIF(NT2_PEDANTIC)

################################################################################
# Add --std=c++0x
################################################################################
OPTION(NT2_0X "Enable/Disable C++0x" OFF)
IF(NT2_0X)
check_cxx_compiler_flag("--std=c++0x" HAS_0X)
IF(HAS_0X)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++0x")
message(STATUS "Enabling C++0x")
ENDIF(HAS_0X)
ENDIF(NT2_0X)

################################################################################
# Handle all type of BUILD_TYPE:
# None (CMAKE_C_FLAGS or CMAKE_CXX_FLAGS used)
# Debug (CMAKE_C_FLAGS_DEBUG or CMAKE_CXX_FLAGS_DEBUG)
# Release (CMAKE_C_FLAGS_RELEASE or CMAKE_CXX_FLAGS_RELEASE)
# RelWithDebInfo (CMAKE_C_FLAGS_RELWITHDEBINFO or CMAKE_CXX_FLAGS_RELWITHDEBINFO
# MinSizeRel (CMAKE_C_FLAGS_MINSIZEREL or CMAKE_CXX_FLAGS_MINSIZEREL) 
################################################################################

ENDIF(CMAKE_COMPILER_IS_GNUCXX)

