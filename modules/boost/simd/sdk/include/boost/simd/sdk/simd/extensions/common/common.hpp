/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_COMMON_COMMON_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_COMMON_COMMON_HPP_INCLUDED

#include <boost/detail/workaround.hpp>

#if !defined(BOOST_SIMD_DETECTED)
#define BOOST_SIMD_NO_SIMD

#define BOOST_SIMD_BYTES      16
#define BOOST_SIMD_BITS       128
#define BOOST_SIMD_STRING     "simd_emulation"
#define BOOST_SIMD_CARDINALS  (2)(4)(8)(16)
#define BOOST_SIMD_DEFAULT_EXTENSION ::boost::simd::tag::simd_emulation_<16u>
#define BOOST_SIMD_DEFAULT_SITE ::boost::dispatch::tag::cpu_

#include <boost/simd/sdk/config/types.hpp>
#if !defined(BOOST_SIMD_SIMD_TYPES)
#include <boost/simd/sdk/simd/extensions/x86/types.hpp>
#endif

#endif

#define BOOST_SIMD_CONFIG_ALIGNMENT BOOST_SIMD_BYTES

////////////////////////////////////////////////////////////////////////////////
// On g++ before 4.3 and MSVC, alignment can't be more than 16
////////////////////////////////////////////////////////////////////////////////
#if (BOOST_WORKAROUND(__GNUC__, == 4) && BOOST_WORKAROUND(__GNUC_MINOR__, < 3)) \
 || defined(BOOST_MSVC)
  #undef  BOOST_SIMD_CONFIG_ALIGNMENT
  #define BOOST_SIMD_CONFIG_ALIGNMENT 16
#endif

#include <boost/simd/sdk/memory/aligned_array.hpp>

#endif
