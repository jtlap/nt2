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
INCLUDE(nt2.info)

################################################################################
# Intel AVX Family
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
# Intel/AMD SSE Family
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
# IBM/Motorola/Apple VMX Family
################################################################################
IF(NT2_PROCESSOR STREQUAL PowerPC)
INCLUDE(arch/FindVMX)
ENDIF()

################################################################################
# Intel/AMD SSE Family fix-up to force arithmetic to be sse style everywhere
################################################################################
IF( NT2_PROCESSOR STREQUAL AMD OR NT2_PROCESSOR STREQUAL X86 OR NT2_PROCESSOR STREQUAL AMD )
  IF( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
    SET ( NT2_CXX_PRECISION_FLAGS "-mfpmath=sse" )
  ENDIF()
ELSE()
  SET ( NT2_CXX_PRECISION_FLAGS "" )
ENDIF()

SET ( NT2_CXX_SIMD_FLAGS "${NT2_SIMD_FLAGS} ${NT2_CXX_PRECISION_FLAGS}"
      CACHE STRING "SIMD extensions compiler flags"
    )

MESSAGE( STATUS "SIMD flag: ${NT2_CXX_SIMD_FLAGS}")
