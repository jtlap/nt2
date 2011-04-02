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
#include <nt2/sdk/simd/extensions/vmx/types.hpp>
#endif

#endif
#endif
