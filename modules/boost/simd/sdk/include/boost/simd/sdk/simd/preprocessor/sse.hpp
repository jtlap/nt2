/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PREPROCESSOR_SSE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PREPROCESSOR_SSE_HPP_INCLUDED

#if defined(BOOST_SIMD_XOP)
  #define BOOST_SIMD_RELATIVE_INCLUDE_BASE(B,F) BOOST_PP_STRINGIZE(B()simd/sse/xop/F) 
#elif defined(BOOST_SIMD_AVX)
  #define BOOST_SIMD_RELATIVE_INCLUDE_BASE(B,F) BOOST_PP_STRINGIZE(B()simd/sse/avx/F) 
#elif defined(BOOST_SIMD_SSE4_2)
  #define BOOST_SIMD_RELATIVE_INCLUDE_BASE(B,F) BOOST_PP_STRINGIZE(B()simd/sse/sse4_2/F) 
#elif defined(BOOST_SIMD_SSE4_1)
  #define BOOST_SIMD_RELATIVE_INCLUDE_BASE(B,F) BOOST_PP_STRINGIZE(B()simd/sse/sse4_1/F) 
#elif defined(BOOST_SIMD_SSSE3)
  #define BOOST_SIMD_RELATIVE_INCLUDE_BASE(B,F) BOOST_PP_STRINGIZE(B()simd/sse/ssse3/F)  
#elif defined(BOOST_SIMD_SSE3)
  #define BOOST_SIMD_RELATIVE_INCLUDE_BASE(B,F) BOOST_PP_STRINGIZE(B()simd/sse/sse3/F) 
#elif defined(BOOST_SIMD_SSE2)
  #define BOOST_SIMD_RELATIVE_INCLUDE_BASE(B,F) BOOST_PP_STRINGIZE(B()simd/sse/sse2/F) 
#endif

#endif
