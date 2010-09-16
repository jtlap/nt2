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
  #define NT2_SIMD_RELATIVE_INCLUDE_BASE(B,F) BOOST_PP_STRINGIZE(B()simd/sse/xop/F) 
#elif defined(NT2_SIMD_AVX)
  #define NT2_SIMD_INCLUDE_BASE() nt2/sdk/simd/details/impl/sse/avx/
  #define NT2_SIMD_RELATIVE_INCLUDE_BASE(B,F) BOOST_PP_STRINGIZE(B()simd/sse/avx/F) 
#elif defined(NT2_SIMD_SSE4_2)
  #define NT2_SIMD_INCLUDE_BASE() nt2/sdk/simd/details/impl/sse/sse4_2/
  #define NT2_SIMD_RELATIVE_INCLUDE_BASE(B,F) BOOST_PP_STRINGIZE(B()simd/sse/sse4_2/F) 
#elif defined(NT2_SIMD_SSE4_1)
  #define NT2_SIMD_INCLUDE_BASE() nt2/sdk/simd/details/impl/sse/sse4_1/
  #define NT2_SIMD_RELATIVE_INCLUDE_BASE(B,F) BOOST_PP_STRINGIZE(B()simd/sse/sse4_1/F) 
#elif defined(NT2_SIMD_SSSE3)
  #define NT2_SIMD_INCLUDE_BASE() nt2/sdk/simd/details/impl/sse/ssse3/
  #define NT2_SIMD_RELATIVE_INCLUDE_BASE(B,F) BOOST_PP_STRINGIZE(B()simd/sse/ssse3/F)  
#elif defined(NT2_SIMD_SSE3)
  #define NT2_SIMD_INCLUDE_BASE() nt2/sdk/simd/details/impl/sse/sse3/
  #define NT2_SIMD_RELATIVE_INCLUDE_BASE(B,F) BOOST_PP_STRINGIZE(B()simd/sse/sse3/F) 
#elif defined(NT2_SIMD_SSE2)
  #define NT2_SIMD_INCLUDE_BASE() nt2/sdk/simd/details/impl/sse/sse2/
  #define NT2_SIMD_RELATIVE_INCLUDE_BASE(B,F) BOOST_PP_STRINGIZE(B()simd/sse/sse2/F) 
#endif

#endif
