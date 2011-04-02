################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Check for Altivec VMX availability
################################################################################
IF( NOT NT2_HAS_VMX_SUPPORT)

################################################################################
# On UNIX, we grep the /proc/cpuinfo entry
################################################################################
IF(NT2_PLATFORM_UNIX)
FIND_FILE(ALTIVEC_SH arch/altivec.sh ${CMAKE_MODULE_PATH})
EXECUTE_PROCESS( COMMAND ${ALTIVEC_SH}
                 OUTPUT_VARIABLE TMP_VMX
                )
ENDIF()

################################################################################
# On OS X, we use systcl
################################################################################
IF(NT2_PLATFORM_OSX)
EXECUTE_PROCESS( COMMAND sysctl -n hw.optional.altivec
                 OUTPUT_VARIABLE TMP_VMX
                )
ENDIF()

STRING(REGEX REPLACE "\n" "" VMX_FOUND ${TMP_VMX})

IF( ${VMX_FOUND} )
MESSAGE( STATUS "PPC Altivec available")
################################################################################
# Find the proper options to compile
################################################################################
check_cxx_compiler_flag("-maltivec" HAS_GCC_VMX)

IF(HAS_GCC_VMX)
set(NT2_SIMD_FLAGS "${NT2_SIMD_FLAGS} -maltivec")
ENDIF()

################################################################################

ELSE()
MESSAGE( STATUS "PPC Altivec not available")
ENDIF()

ENDIF()


