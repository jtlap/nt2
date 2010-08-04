/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_EXTENSIONS_SSE_MMX_HPP_INCLUDED
#define NT2_SDK_SIMD_EXTENSIONS_SSE_MMX_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// No SIMD extensions have been found yet
////////////////////////////////////////////////////////////////////////////////
#if !defined(NT2_SIMD_DETECTED) && defined(NT2_HAS_MMX_SUPPORT)

////////////////////////////////////////////////////////////////////////////////
// Check for MMX
////////////////////////////////////////////////////////////////////////////////
#if defined(__MMX__)

////////////////////////////////////////////////////////////////////////////////
// Report MMX discovery
////////////////////////////////////////////////////////////////////////////////
NT2_WARNING(MMX SIMD extention detected)

////////////////////////////////////////////////////////////////////////////////
// MMX extensions flags
////////////////////////////////////////////////////////////////////////////////
#define NT2_SIMD_DETECTED
#define NT2_SIMD_MMX
#define NT2_SIMD_SSE_FAMILY
#define NT2_SIMD_STRING             "MMX"
#define NT2_SIMD_BYTES              8
#define NT2_SIMD_BITS               64
#define NT2_SIMD_CARDINALS          (1)(2)(4)(8)
#define NT2_SIMD_DEFAULT_EXTENSION  ::nt2::tag::mmx_

#include <mmmintrin.h>
#include <nt2/sdk/simd/extensions/meta/mmx.hpp>

#endif
#endif
#endif
