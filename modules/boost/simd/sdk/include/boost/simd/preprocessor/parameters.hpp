//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREPROCESSOR_PARAMETERS_HPP_INCLUDED
#define BOOST_SIMD_PREPROCESSOR_PARAMETERS_HPP_INCLUDED

#include <boost/simd/sdk/config/arch.hpp>
#include <boost/simd/sdk/simd/extensions.hpp>

#if defined(DOXYGEN_ONLY)
/*!
  @brief System dependent value for SIMD alignment

  This macro is defined to be equal to the current system required alignment
  for proper SIMD code execution.
**/
#define BOOST_SIMD_CONFIG_ALIGNMENT BOOST_SIMD_CONFIG_ALIGNMENT
#else
#define BOOST_SIMD_CONFIG_ALIGNMENT BOOST_SIMD_BYTES
#endif


#if defined(DOXYGEN_ONLY)
/*!
  @brief System dependent value for alloca alignment

  This macro is defined to be equal to the current system alignment of
  address returned by @c alloca.
**/
#define BOOST_SIMD_CONFIG_ALIGNMENT BOOST_SIMD_CONFIG_ALIGNMENT
#else

// Fix for GCC Bug 35271 : http://gcc.gnu.org/bugzilla/show_bug.cgi?id=35271
#if BOOST_SIMD_GCC_VERSION < 40203
#define BOOST_SIMD_STACK_ALIGNMENT 8
#else
#define BOOST_SIMD_STACK_ALIGNMENT BOOST_SIMD_ARCH_ALIGNMENT
#endif

#endif

#endif
