/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_EXTENSIONS_ALTIVEC_HPP_INCLUDED
#define NT2_SDK_SIMD_EXTENSIONS_ALTIVEC_HPP_INCLUDED

#include <nt2/sdk/simd/meta/as_simd.hpp>
#include <nt2/sdk/simd/meta/extension_of.hpp>
#include <nt2/sdk/simd/meta/is_simd_specific.hpp>

////////////////////////////////////////////////////////////////////////////////
// No SIMD extensions have been found yet
////////////////////////////////////////////////////////////////////////////////
#if !defined(NT2_SIMD_DETECTED)
#include <nt2/sdk/simd/extensions/vmx/altivec.hpp>
//#include <nt2/sdk/simd/extensions/vmx/spu.hpp>

#if defined(NT2_SIMD_VMX_FAMILY)
#define NT2_SIMD_TYPES  (float)(nt2::uint32_t)(nt2::int32_t)  \
                        (nt2::uint16_t)(nt2::int16_t)         \
                        (nt2::uint8_t)(nt2::int8_t)           \
                        /**/

#define NT2_SIMD_REAL (float)

#define NT2_SIMD_UNSIGNED_TYPES (nt2::uint32_t)(nt2::uint16_t)(nt2::uint8_t)

#define NT2_SIMD_SIGNED_TYPES (nt2::int64_t)(nt2::int32_t)        \
                              (float)(nt2::int16_t)(nt2::int8_t)  \
                              /**/

#define NT2_SIMD_INTEGRAL_SIGNED_TYPES    (nt2::int32_t)(nt2::int16_t)(nt2::int8_t)
#define NT2_SIMD_INTEGRAL_UNSIGNED_TYPES  (nt2::uint32_t)(nt2::uint16_t)(nt2::uint8_t)

#endif

#endif
#endif
