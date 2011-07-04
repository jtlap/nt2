/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_CONFIG_BOOTSTRAP_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_BOOTSTRAP_HPP_INCLUDED

#if defined(BOOST_SIMD_CUSTOM_BOOTSTRAP)
#include <boost/preprocessor/stringize.hpp>
#include <boost/simd/sdk/details/preprocessor.hpp>

#define BOOST_SIMD_CONFIG_BASE()	boost/simd/extension/config/
#include BOOST_SIMD_PP_INCLUDE(BOOST_SIMD_CONFIG_BASE,BOOST_SIMD_CUSTOM_BOOTSTRAP)
#else
////////////////////////////////////////////////////////////////////////////////
// SIMD Capabilities
////////////////////////////////////////////////////////////////////////////////
#cmakedefine BOOST_SIMD_HAS_MMX_SUPPORT
#cmakedefine BOOST_SIMD_HAS_SSE2_SUPPORT
#cmakedefine BOOST_SIMD_HAS_SSE3_SUPPORT
#cmakedefine BOOST_SIMD_HAS_SSSE3_SUPPORT
#cmakedefine BOOST_SIMD_HAS_SSE4_1_SUPPORT
#cmakedefine BOOST_SIMD_HAS_SSE4_2_SUPPORT
#cmakedefine BOOST_SIMD_HAS_AVX_SUPPORT
#cmakedefine BOOST_SIMD_HAS_XOP_SUPPORT
#cmakedefine BOOST_SIMD_HAS_FMA4_SUPPORT
#cmakedefine BOOST_SIMD_HAS_VMX_SUPPORT

#endif

#endif

