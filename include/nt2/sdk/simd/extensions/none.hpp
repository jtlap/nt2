/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_EXTENSIONS_NONE_HPP_INCLUDED
#define NT2_SDK_SIMD_EXTENSIONS_NONE_HPP_INCLUDED

#include <nt2/sdk/simd/meta/as_simd.hpp>
#include <nt2/sdk/simd/meta/extension_of.hpp>
#include <nt2/sdk/simd/meta/is_simd_specific.hpp>

#if !defined(NT2_SIMD_DETECTED)
NT2_WARNING(No SIMD extensions detected)
#define NT2_NO_SIMD

////////////////////////////////////////////////////////////////////////////////
// If no SIMD extension are set, we still need to align on 128 bits to allow
// linking with SIMD enabled obejct files
////////////////////////////////////////////////////////////////////////////////
#define NT2_SIMD_BYTES      16
#define NT2_SIMD_BITS       128
#define NT2_SIMD_STRING     "none"
#define NT2_SIMD_CARDINALS (1)

#if defined(NT2_SIMD_TYPES)
#define NT2_SIMD_TYPES
#define NT2_SIMD_REAL
#define NT2_SIMD_UNSIGNED_TYPES
#define NT2_SIMD_SIGNED_TYPES
#define NT2_SIMD_INTEGRAL_SIGNED_TYPES
#define NT2_SIMD_INTEGRAL_UNSIGNED_TYPES
#endif

#endif

#endif
