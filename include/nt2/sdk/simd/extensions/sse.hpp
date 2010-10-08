/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_EXTENSIONS_SSE_HPP_INCLUDED
#define NT2_SDK_SIMD_EXTENSIONS_SSE_HPP_INCLUDED
#include <nt2/sdk/config/type_lists.hpp>

#include <nt2/sdk/simd/meta/as_simd.hpp>
#include <nt2/sdk/simd/meta/extension_of.hpp>
#include <nt2/sdk/simd/meta/is_simd_specific.hpp>

#if !defined(NT2_SIMD_DETECTED)
////////////////////////////////////////////////////////////////////////////////
// Check for the most recent SSE familly extension
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/simd/extensions/sse/xop.hpp>
#include <nt2/sdk/simd/extensions/sse/sse4a.hpp>

//* TODO: #include <nt2/sdk/simd/extensions/sse/fma4.hpp>
#include <nt2/sdk/simd/extensions/sse/avx.hpp>
#include <nt2/sdk/simd/extensions/sse/sse4_2.hpp>
#include <nt2/sdk/simd/extensions/sse/sse4_1.hpp>
#include <nt2/sdk/simd/extensions/sse/ssse3.hpp>
#include <nt2/sdk/simd/extensions/sse/sse3.hpp>
#include <nt2/sdk/simd/extensions/sse/sse2.hpp>

#if !defined(NT2_TYPES)
#define NT2_SIMD_TYPES  NT2_TYPES
/**/
#endif

#if !defined(NT2_SIMD_REAL_CONVERTIBLE_TYPES)
/**/
#endif

#if !defined(NT2_SIMD_INTEGRAL_SIGNED_TYPES)
#define NT2_SIMD_INTEGRAL_SIGNED_TYPES NT2_INTEGRAL_SIGNED_TYPES
/**/
#endif

#if !defined(NT2_SIMD_UNSIGNED_TYPES)
#define NT2_SIMD_UNSIGNED_TYPES NT2_UNSIGNED_TYPES
/**/
#endif

#if !defined(NT2_SIMD_INTEGRAL_TYPES)
#define NT2_SIMD_INTEGRAL_TYPES NT2_INTEGRAL_TYPES
/**/
#endif

#if !defined(NT2_SIMD_SIGNED_TYPES)
#define NT2_SIMD_SIGNED_TYPES NT2_SIGNED_TYPES
/**/
#endif

#endif
#endif

