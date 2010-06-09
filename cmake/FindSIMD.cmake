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
include(FindMMX)
include(FindSSE2)
include(FindSSSE3)
include(FindSSE3)

################################################################################
# Find SSE4_1
################################################################################
SET(SIMD_VAR      SSE4_1_FOUND )
SET(SIMD_FLAGS    ssse4.1      )
SET(SIMD_INCLUDE  smmintrin.h  )
SET(SIMD_TYPE     __m128d      )
SET(SIMD_OP       _mm_add_pd   )
include(FindSIMDExtensions)

################################################################################
# Find SSE4_2
################################################################################
SET(SIMD_VAR      SSE4_2_FOUND )
SET(SIMD_FLAGS    ssse4.2      )
SET(SIMD_INCLUDE  smmintrin.h  )
SET(SIMD_TYPE     __m128d      )
SET(SIMD_OP       _mm_add_pd   )
include(FindSIMDExtensions)

################################################################################
# Find SSE4A
################################################################################
SET(SIMD_VAR      SSE4A_FOUND )
SET(SIMD_FLAGS    ssse4a      )
SET(SIMD_INCLUDE  ammintrin.h )
SET(SIMD_TYPE     __m128d     )
SET(SIMD_OP       _mm_add_pd  )
include(FindSIMDExtensions)

################################################################################
# Find AVX
################################################################################
SET(SIMD_VAR      AVX_FOUND     )
SET(SIMD_FLAGS    avx           )
SET(SIMD_INCLUDE  imintrin.h    )
SET(SIMD_TYPE     __m256        )
SET(SIMD_OP       _mm256_add_ps )
include(FindSIMDExtensions)

