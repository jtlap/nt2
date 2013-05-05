//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_CONFIG_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_CONFIG_HPP_INCLUDED

/*!
  @file
  @brief Defines system dependent macro related to memory management
**/
#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/config/compiler.hpp>

#if (     (defined _GNU_SOURCE)                                   \
      ||  ((defined _XOPEN_SOURCE) && (_XOPEN_SOURCE >= 600))     \
    )                                                             \
 && (defined _POSIX_ADVISORY_INFO) && (_POSIX_ADVISORY_INFO > 0)
  /// INTERNAL ONLY
  #define BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN
#endif

#if defined(DOXYGEN_ONLY)
/*!
  @brief Malloc-like behavior flag

  Used on function definition, BOOST_SIMD_MALLOC flags the current function
  as having a behavior similar to @a malloc. This allows some compilers to
  optimize the code using pointer returned by such function.

  @par Usage:

  @include memory/simd_malloc.cpp
**/
#define BOOST_SIMD_MALLOC
#else
#if defined(BOOST_SIMD_COMPILER_MSVC)
#define BOOST_SIMD_MALLOC   __declspec(restrict)
#elif defined(BOOST_SIMD_GCC_LIKE)
#define BOOST_SIMD_MALLOC   __attribute__ ((malloc))
#else
#define BOOST_SIMD_MALLOC
#endif
#endif

#endif
