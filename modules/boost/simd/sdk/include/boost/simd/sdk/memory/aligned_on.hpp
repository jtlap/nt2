//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_MEMORY_ALIGNED_ON_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_ALIGNED_ON_HPP_INCLUDED

#include <boost/config.hpp>

////////////////////////////////////////////////////////////////////////////////
// Intrinsic platform dependant alignment attribute
////////////////////////////////////////////////////////////////////////////////
#if (defined(BOOST_MSVC))
#define BOOST_SIMD_ALIGN_ON(x)  __declspec(align(x))
#elif (defined(__GNUC__)) || (defined(__xlC__))
#define BOOST_SIMD_ALIGN_ON(x)  __attribute__(( __aligned__((x)) ))
#elif !(defined(__WAVE__))
#error boost::simd::aligned - No Supported alignment attribute
#endif

#endif
