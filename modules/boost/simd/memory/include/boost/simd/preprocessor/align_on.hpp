//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//         Copyright 2013          Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREPROCESSOR_ALIGN_ON_HPP_INCLUDED
#define BOOST_SIMD_PREPROCESSOR_ALIGN_ON_HPP_INCLUDED

#include <boost/config.hpp>

#if defined(DOXYGEN_ONLY)
/*!
  @brief Macro wrapper for alignment attribute

  Provides a portable access to various compiler specific attributes
  flagging types as aligned on a given boundary.

  @par Usage:

  @include preprocessor/align_on.cpp

  @param ALIGN Power of two alignment boundary to apply
**/
#define BOOST_SIMD_ALIGN_ON(ALIGN)
#else
#if defined(BOOST_MSVC)
#define BOOST_SIMD_ALIGN_ON(ALIGN)  __declspec(align(ALIGN))
#elif (defined(__GNUC__)) || (defined(__xlC__))
#define BOOST_SIMD_ALIGN_ON(ALIGN)  __attribute__(( __aligned__((ALIGN)) ))
#elif !(defined(__WAVE__))
#error BOOST_SIMD_ALIGN_ON - No Supported alignment attribute
#endif
#endif

#endif
