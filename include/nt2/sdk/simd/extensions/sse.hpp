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

#if defined(NT2_SIMD_SSE_FAMILY)
#define NT2_SIMD_TYPES  (double)(nt2::uint64_t)(nt2::int64_t) \
                        (float)(nt2::uint32_t)(nt2::int32_t)  \
                        (nt2::uint16_t)(nt2::int16_t)         \
                        (nt2::uint8_t)(nt2::int8_t)           \
                        /**/

#define NT2_SIMD_REAL_TYPES (double)(float)

#define NT2_SIMD_UNSIGNED_TYPES (nt2::uint64_t)(nt2::uint32_t)  \
                                (nt2::uint16_t)(nt2::uint8_t)   \
                                /**/

#define NT2_SIMD_SIGNED_TYPES (double)(nt2::int64_t)(nt2::int32_t)  \
                              (float)(nt2::int16_t)(nt2::int8_t)    \
                              /**/

#define NT2_SIMD_INTEGRAL_UNSIGNED_TYPES  (nt2::uint64_t)(nt2::uint32_t)  \
                                          (nt2::uint16_t)(nt2::uint8_t)   \
                                          /**/

#define NT2_SIMD_INTEGRAL_SIGNED_TYPES  (nt2::int64_t)(nt2::int32_t)  \
                                        (nt2::int16_t)(nt2::int8_t)   \
                                        /**/

#define NT2_SIMD_REAL_CONVERTIBLE_TYPES  (nt2::int64_t)(nt2::int32_t)  \
                                         (nt2::uint64_t)(nt2::uint32_t)  \
                                         (double)(float) \
                                        /**/

#endif

#endif
#endif

