/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_SSE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_SSE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Check for the most recent SSE familly extension
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/simd/extensions/sse/xop.hpp>
#include <boost/simd/sdk/simd/extensions/sse/fma4.hpp>
#include <boost/simd/sdk/simd/extensions/sse/avx.hpp>
#include <boost/simd/sdk/simd/extensions/sse/sse4_2.hpp>
#include <boost/simd/sdk/simd/extensions/sse/sse4_1.hpp>
#include <boost/simd/sdk/simd/extensions/sse/ssse3.hpp>
#include <boost/simd/sdk/simd/extensions/sse/sse4a.hpp>
#include <boost/simd/sdk/simd/extensions/sse/sse3.hpp>
#include <boost/simd/sdk/simd/extensions/sse/sse2.hpp>
#include <boost/simd/sdk/simd/extensions/sse/sse.hpp>

#if defined(BOOST_SIMD_SSE_FAMILY)
#include <boost/simd/sdk/simd/extensions/sse/types.hpp>
#endif

#endif

