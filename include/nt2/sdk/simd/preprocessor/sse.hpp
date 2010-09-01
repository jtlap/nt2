/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PREPROCESSOR_SSE_HPP_INCLUDED
#define NT2_SDK_SIMD_PREPROCESSOR_SSE_HPP_INCLUDED

#if defined(NT2_SIMD_XOP)
  #define NT2_SIMD_INCLUDE_BASE() nt2/sdk/simd/details/impl/sse/xop/
  #define NT2_SIMD_RELATIVE_INCLUDE_BASE(X) X()simd/sse/xop/
#elif defined(NT2_SIMD_AVX)
  #define NT2_SIMD_INCLUDE_BASE() nt2/sdk/simd/details/impl/sse/avx/
  #define NT2_SIMD_RELATIVE_INCLUDE_BASE(X) X()simd/sse/avx/
#elif (defined(NT2_SIMD_SSE4_2)
  #define NT2_SIMD_INCLUDE_BASE() nt2/sdk/simd/details/impl/sse/sse4_2/
  #define NT2_SIMD_RELATIVE_INCLUDE_BASE(X) X()simd/sse/sse4_2/
#elif defined( NT2_SIMD_SSE4_1))
  #define NT2_SIMD_INCLUDE_BASE() nt2/sdk/simd/details/impl/sse/sse4_1/
  #define NT2_SIMD_RELATIVE_INCLUDE_BASE(X) X()simd/sse/sse4_1/
#elif defined(NT2_SIMD_SSSE3)
  #define NT2_SIMD_INCLUDE_BASE() nt2/sdk/simd/details/impl/sse/ssse3/
  #define NT2_SIMD_RELATIVE_INCLUDE_BASE(X) X()simd/sse/ssse3/
#elif defined(NT2_SIMD_SSE3)
  #define NT2_SIMD_INCLUDE_BASE() nt2/sdk/simd/details/impl/sse/sse3/
  #define NT2_SIMD_RELATIVE_INCLUDE_BASE(X) X()simd/sse/sse3/
#elif defined(NT2_SIMD_SSE2)
  #define NT2_SIMD_INCLUDE_BASE() nt2/sdk/simd/details/impl/sse/sse2/
  #define NT2_SIMD_RELATIVE_INCLUDE_BASE(X) X()simd/sse/sse2/
#endif

#endif
