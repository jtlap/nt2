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

#include <boost/cstdint.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/placeholders.hpp>
#include <nt2/sdk/simd/meta/as_simd.hpp>
#include <nt2/sdk/simd/meta/extension_of.hpp>
#include <nt2/sdk/simd/meta/is_simd_specific.hpp>

#if !defined(NT2_SIMD_DETECTED)
#if defined(NT2_VERBOSE)
#warning NT2 Configuration: No SIMD extensions detected.
#endif

////////////////////////////////////////////////////////////////////////////////
// If no SIMD extension are set, we still need to align on 128 bits to allow
// linking with SIMD enabled obejct files
////////////////////////////////////////////////////////////////////////////////
#define NT2_SIMD_BYTES      16
#define NT2_SIMD_BITS       128
#define NT2_SIMD_STRING     "none"
#define NT2_SIMD_CARDINALS (1)

#endif

#endif
