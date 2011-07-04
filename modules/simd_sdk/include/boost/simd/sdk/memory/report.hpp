/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_MEMORY_REPORT_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_REPORT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Memory config header
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/memory/config.hpp>
#include <boost/simd/sdk/config/details/reporter.hpp>

namespace boost { namespace simd {  namespace config
{
  //////////////////////////////////////////////////////////////////////////////
  // Memory configuration status reporter
  //////////////////////////////////////////////////////////////////////////////
  inline void memories()
  {
    printf(" Memory alignment        : %d\n", BOOST_SIMD_CONFIG_ALIGNMENT );
    #if defined(BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN)
      puts(" Memory allocation       : posix_memalign");
    #elif defined(_MSC_VER)
      puts(" Memory allocation       : _aligned_malloc");
    #else
      puts(" Memory allocation       : pointer stashing");
    #endif
    puts("");
  }

  BOOST_SIMD_REGISTER_STATUS(memories);
} } }

#endif
