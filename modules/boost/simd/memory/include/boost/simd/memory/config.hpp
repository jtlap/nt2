//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013          MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_CONFIG_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_CONFIG_HPP_INCLUDED

/*!
  @file
  @brief Defines system dependent macro and type
**/
#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/config/compiler.hpp>

#if defined(NT2_DOXYGEN_ONLY)
/*!
  @brief POSIX compliance detection

  If BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN is defined, current system is
  able to use posix_memalign as a base for aligned memory allocation functions.
**/
#define BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN
#else
#if (     (defined _GNU_SOURCE)                                   \
      ||  ((defined _XOPEN_SOURCE) && (_XOPEN_SOURCE >= 600))     \
    )                                                             \
 && (defined _POSIX_ADVISORY_INFO) && (_POSIX_ADVISORY_INFO > 0)
  #define BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN
#endif
#endif

#if defined(NT2_DOXYGEN_ONLY)
/*!
  @brief Malloc-like behavior flag

  Use don function definition, BOOST_SIMD_MALLOC flags the current function
  as havign a behavior similar to malloc. This allows some compilers to optimize
  the code using pointer returned by such function.

  @see allocate
  @see aligned_malloc
**/
#define BOOST_SIMD_MALLOC
#else
/// Make allocation function improve optimization by compilers
#if defined(BOOST_SIMD_COMPILER_MSVC)
#define BOOST_SIMD_MALLOC   __declspec(restrict)
#elif defined(BOOST_SIMD_GCC_LIKE)
#define BOOST_SIMD_MALLOC   __attribute__ ((malloc))
#else
#define BOOST_SIMD_MALLOC
#endif
#endif

namespace boost { namespace simd {  namespace memory
{
  /*!
    @brief Portable byte typedef

    @c byte is defined as the current system type usable to allocate bytes.
  **/
  typedef boost::simd::uint8_t byte;
} } }

#endif
