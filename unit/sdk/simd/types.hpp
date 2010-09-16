/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_UNIT_SDK_SIMD_TYPES_HPP_INCLUDED
#define NT2_UNIT_SDK_SIMD_TYPES_HPP_INCLUDED

#include <nt2/sdk/simd/extensions.hpp>

////////////////////////////////////////////////////////////////////////////////
// Generates sequence of supported types for SIMD
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_SIMD_SSE_FAMILY)
#define NT2_SIMD_TYPES  (double)(nt2::uint64_t)(nt2::int64_t) \
                        (float)(nt2::uint32_t)(nt2::int32_t)  \
                        (nt2::uint16_t)(nt2::int16_t)         \
                        (nt2::uint8_t)(nt2::int8_t)           \
/**/
#elif defined(NT2_SIMD_VMX_FAMILY)
#define NT2_SIMD_TYPES  (float)(nt2::uint32_t)(nt2::int32_t)  \
                        (nt2::uint16_t)(nt2::int16_t)         \
                        (nt2::uint8_t)(nt2::int8_t)           \
/**/
#endif

#endif
