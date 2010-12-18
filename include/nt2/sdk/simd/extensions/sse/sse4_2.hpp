/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_EXTENSIONS_SSE_SSE4_2_HPP_INCLUDED
#define NT2_SDK_SIMD_EXTENSIONS_SSE_SSE4_2_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// No SIMD extensions have been found yet
////////////////////////////////////////////////////////////////////////////////
#if !defined(NT2_SIMD_DETECTED) && defined(NT2_HAS_SSE4_2_SUPPORT)

////////////////////////////////////////////////////////////////////////////////
// Check for SSE4_2
////////////////////////////////////////////////////////////////////////////////
#if defined(__SSE4_2__)

////////////////////////////////////////////////////////////////////////////////
// Report  SSE4_2 discovery
////////////////////////////////////////////////////////////////////////////////
NT2_WARNING(SSE4_2 SIMD extension detected)

////////////////////////////////////////////////////////////////////////////////
//  SSE4_2 extensions flags
////////////////////////////////////////////////////////////////////////////////
#define NT2_SIMD_DETECTED
#define NT2_SIMD_SSE4_2
#define NT2_SIMD_SSE_FAMILY
#define NT2_SIMD_STRING             "SSE4_2"
#define NT2_SIMD_STRING_LIST        "SSE2 SSE3 SSSE3 SSE4_1 SSE4_2"
#define NT2_SIMD_BYTES              16
#define NT2_SIMD_BITS               128
#define NT2_SIMD_CARDINALS          (2)(4)(8)(16)
#define NT2_SIMD_TAG_SEQ            (::nt2::tag::sse_)
#define NT2_SIMD_DEFAULT_EXTENSION  ::nt2::tag::sse_

extern "C"
{
  #include <smmintrin.h>
}

#include <nt2/sdk/simd/extensions/meta/sse.hpp>

#endif
#endif
#endif
