################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Check for SIMD extensions availability
################################################################################

################################################################################
# Intel AVX Familly
################################################################################
IF(NT2_PROCESSOR STREQUAL X86)
INCLUDE(arch/FindAVX)
ENDIF()

################################################################################
# AMD XOP
################################################################################
IF( NT2_PROCESSOR STREQUAL AMD)
INCLUDE(arch/FindXOP)
ENDIF()

################################################################################
# Intel/AMD SSE Familly
################################################################################
IF( NT2_PROCESSOR STREQUAL X86 OR NT2_PROCESSOR STREQUAL AMD )
INCLUDE(arch/FindFMA4)
INCLUDE(arch/FindSSE4)
INCLUDE(arch/FindSSSE3)
INCLUDE(arch/FindSSE3)
INCLUDE(arch/FindSSE2)
INCLUDE(arch/FindMMX)
ENDIF()

################################################################################
# IBM/Motorola/Apple VMX Familly
################################################################################
IF(NT2_PROCESSOR STREQUAL PowerPC)
INCLUDE(arch/FindVMX)
ENDIF()

SET ( NT2_CXX_SIMD_FLAGS "${NT2_SIMD_FLAGS}"
      CACHE STRING "SIMD extensions compiler flags"
    )

MESSAGE( STATUS "SIMD flag: ${NT2_CXX_SIMD_FLAGS}")
