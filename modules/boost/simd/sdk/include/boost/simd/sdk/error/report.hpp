//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_ERROR_REPORT_HPP_INCLUDED
#define BOOST_SIMD_SDK_ERROR_REPORT_HPP_INCLUDED

//==============================================================================
// Configuration report for error handling settings
//==============================================================================
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/error/debug.hpp>

namespace boost { namespace simd { namespace config
{
  static void errors()
  {
    #if defined(BOOST_SIMD_RELEASE)
    puts(" Compilation mode        : release");
    #elif defined(BOOST_SIMD_DEBUG)
    puts(" Compilation mode        : debug");
    #else
    puts(" Compilation mode        : normal");
    #endif

    #if defined(BOOST_SIMD_DISABLE_ASSERTS)
    puts(" Assertion Failures      : disabled");
    #else
    puts(" Assertion Failures      : enabled");
    #endif

    #if defined(BOOST_SIMD_USE_CONCEPTS)
    puts(" Concepts checks         : enabled");
    #else
    puts(" Concepts checks         : disabled");
    #endif
    puts("");
  }

  BOOST_SIMD_REGISTER_STATUS(errors);
} } }

#endif
