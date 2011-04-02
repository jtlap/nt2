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

#include <nt2/sdk/simd/meta/as_simd.hpp>
#include <nt2/sdk/simd/meta/extension_of.hpp>
#include <nt2/sdk/simd/meta/is_simd_specific.hpp>

#if !defined(NT2_SIMD_DETECTED)
////////////////////////////////////////////////////////////////////////////////
// Check for the most recent SSE familly extension
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/simd/extensions/sse/xop.hpp>
#include <nt2/sdk/simd/extensions/sse/sse4a.hpp>

//#include <nt2/sdk/simd/extensions/sse/fma4.hpp>
#include <nt2/sdk/simd/extensions/sse/avx.hpp>
#include <nt2/sdk/simd/extensions/sse/sse4_2.hpp>
#include <nt2/sdk/simd/extensions/sse/sse4_1.hpp>
#include <nt2/sdk/simd/extensions/sse/ssse3.hpp>
#include <nt2/sdk/simd/extensions/sse/sse3.hpp>
#include <nt2/sdk/simd/extensions/sse/sse2.hpp>

#if defined(NT2_SIMD_SSE_FAMILY)
#include <nt2/sdk/simd/extensions/sse/types.hpp>
#endif

#endif
#endif

