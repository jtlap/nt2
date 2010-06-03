################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Find about SIMD
################################################################################
include(FindSIMD)

IF(${MMX_FOUND})
SET(NT2_HAS_MMX_SUPPORT 1)
ENDIF()

IF(SSE2_FOUND)
SET(NT2_HAS_SSE2_SUPPORT 1)
ENDIF(SSE2_FOUND)

IF(SSE3_FOUND)
SET(NT2_HAS_SSE3_SUPPORT 1)
ENDIF(SSE3_FOUND)

IF(SSSE3_FOUND)
SET(NT2_HAS_SSSE3_SUPPORT 1)
ENDIF(SSSE3_FOUND)

IF(SSE4_1_FOUND)
SET(NT2_HAS_SSE4_1_SUPPORT 1)
ENDIF(SSE4_1_FOUND)

IF(SSE4_2_FOUND)
SET(NT2_HAS_SSE4_2_SUPPORT 1)
ENDIF(SSE4_2_FOUND)

IF(SSE4A_FOUND)
SET(NT2_HAS_SSE4A_SUPPORT 1)
ENDIF(SSE4A_FOUND)

IF(AVX_FOUND)
SET(NT2_HAS_AVX_SUPPORT 1)
ENDIF(AVX_FOUND)

IF(VMX_FOUND)
SET(NT2_HAS_VMX_SUPPORT 1)
ENDIF(VMX_FOUND)

