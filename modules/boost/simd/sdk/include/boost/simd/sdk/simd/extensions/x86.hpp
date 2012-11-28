/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_X86_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_X86_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Check for the most recent SSE family extension
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/simd/extensions/x86/lrb.hpp>

#ifndef BOOST_SIMD_HAS_LRB_SUPPORT
#include <boost/simd/sdk/simd/extensions/x86/xop.hpp>
#include <boost/simd/sdk/simd/extensions/x86/fma4.hpp>
#include <boost/simd/sdk/simd/extensions/x86/avx.hpp>
#include <boost/simd/sdk/simd/extensions/x86/sse4_2.hpp>
#include <boost/simd/sdk/simd/extensions/x86/sse4_1.hpp>
#include <boost/simd/sdk/simd/extensions/x86/ssse3.hpp>
#include <boost/simd/sdk/simd/extensions/x86/sse4a.hpp>
#include <boost/simd/sdk/simd/extensions/x86/sse3.hpp>
#include <boost/simd/sdk/simd/extensions/x86/sse2.hpp>
#include <boost/simd/sdk/simd/extensions/x86/sse.hpp>
#endif

#if defined(BOOST_SIMD_LRB_FAMILY)
#include <boost/simd/sdk/simd/extensions/lrb/types.hpp>
#elif defined(BOOST_SIMD_SSE_FAMILY)
#include <boost/simd/sdk/simd/extensions/x86/types.hpp>
#endif

#endif
