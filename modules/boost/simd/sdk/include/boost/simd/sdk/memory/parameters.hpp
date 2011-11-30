/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_MEMORY_PARAMETERS_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_PARAMETERS_HPP_INCLUDED
//TODO compute alignement according instruction set
//nosimd -> 0 sse2 -> 16 avx -> 32 altivec ? etc.
#include <cstddef>
#include <boost/detail/workaround.hpp>
#include <boost/simd/sdk/simd/extensions.hpp>

////////////////////////////////////////////////////////////////////////////////
// Selecting alignment with the extension family
////////////////////////////////////////////////////////////////////////////////
#if defined(BOOST_SIMD_DETECTED) && defined(BOOST_SIMD_SSE_FAMILY)
#define BOOST_SIMD_CONFIG_ALIGNMENT 32
#elif defined(BOOST_SIMD_DETECTED) && defined(BOOST_SIMD_VMX_FAMILY)
#define BOOST_SIMD_CONFIG_ALIGNMENT 16
#else 
#define BOOST_SIMD_CONFIG_ALIGNMENT 16
#endif

////////////////////////////////////////////////////////////////////////////////
// On g++ before 4.3, alignment can't be more than 16
////////////////////////////////////////////////////////////////////////////////
#if BOOST_WORKAROUND(__GNUC__, == 4) && BOOST_WORKAROUND(__GNUC_MINOR__, < 3)
  #undef  BOOST_SIMD_CONFIG_ALIGNMENT
  #define BOOST_SIMD_CONFIG_ALIGNMENT 16
#endif

#endif
