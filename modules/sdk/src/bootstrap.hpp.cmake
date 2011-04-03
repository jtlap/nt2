/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONFIG_BOOTSTRAP_HPP_INCLUDED
#define NT2_SDK_CONFIG_BOOTSTRAP_HPP_INCLUDED

#if defined(NT2_CUSTOM_BOOTSTRAP)
#include <boost/preprocessor/stringize.hpp>
#include <nt2/sdk/details/preprocessor.hpp>

#define NT2_CONFIG_BASE()	nt2/extension/config/
#include NT2_PP_INCLUDE(NT2_CONFIG_BASE,NT2_CUSTOM_BOOTSTRAP)
#else
////////////////////////////////////////////////////////////////////////////////
// SIMD Capabilities
////////////////////////////////////////////////////////////////////////////////
#cmakedefine NT2_HAS_MMX_SUPPORT
#cmakedefine NT2_HAS_SSE2_SUPPORT
#cmakedefine NT2_HAS_SSE3_SUPPORT
#cmakedefine NT2_HAS_SSSE3_SUPPORT
#cmakedefine NT2_HAS_SSE4_1_SUPPORT
#cmakedefine NT2_HAS_SSE4_2_SUPPORT
#cmakedefine NT2_HAS_AVX_SUPPORT
#cmakedefine NT2_HAS_XOP_SUPPORT
#cmakedefine NT2_HAS_FMA4_SUPPORT
#cmakedefine NT2_HAS_VMX_SUPPORT

#endif

#endif

