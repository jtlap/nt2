/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_EXTENSIONS_SSE_FMA4_HPP_INCLUDED
#define NT2_SDK_SIMD_EXTENSIONS_SSE_FMA4_HPP_INCLUDED

#if defined(__FMA4__)
#  ifndef NT2_HAS_FMA4_SUPPORT
#    define NT2_HAS_FMA4_SUPPORT
#  endif
#elif defined(NT2_HAS_FMA4_SUPPORT) && !defined(_MSC_VER)
#  undef NT2_HAS_FMA4_SUPPORT
#endif

#ifdef NT2_HAS_FMA4_SUPPORT
#  ifndef NT2_HAS_AVX_SUPPORT
#    define NT2_HAS_AVX_SUPPORT
#  endif
#  ifndef NT2_HAS_SSE4A_SUPPORT
#    define NT2_HAS_SSE4A_SUPPORT
#  endif
#endif

#if !defined(NT2_SIMD_DETECTED) && defined(NT2_HAS_FMA4_SUPPORT)

////////////////////////////////////////////////////////////////////////////////
// Report FMA4 discovery
////////////////////////////////////////////////////////////////////////////////
NT2_WARNING(FMA4 SIMD extension detected)

////////////////////////////////////////////////////////////////////////////////
// FMA4 extensions flags
////////////////////////////////////////////////////////////////////////////////
#define NT2_SIMD_DETECTED
#define NT2_SIMD_FMA4
#define NT2_SIMD_SSE_FAMILY
#define NT2_SIMD_STRING             "FMA4"
#define NT2_SIMD_STRING_LIST        "SSE2 SSE3 SSE4A SSSE3 SSE4_1 SSE4_2 AVX FMA4"
#define NT2_SIMD_BYTES              32
#define NT2_SIMD_BITS               256
#define NT2_SIMD_CARDINALS          (2)(4)(8)(16)(32)
#define NT2_SIMD_TAG_SEQ            (::nt2::tag::avx_)(::nt2::tag::sse_)
#define NT2_SIMD_DEFAULT_EXTENSION  ::nt2::tag::avx_
#define NT2_SIMD_DEFAULT_SITE       ::nt2::tag::avx_

#include <immintrin.h>

#include <nt2/sdk/simd/extensions/meta/sse.hpp>
#include <nt2/sdk/simd/extensions/meta/avx.hpp>

#endif
#endif
