/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_REPORT_HPP_INCLUDED
#define NT2_SDK_MEMORY_REPORT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Memory config header
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/memory/config.hpp>
#include <nt2/sdk/config/details/reporter.hpp>

namespace nt2 { namespace config
{
  //////////////////////////////////////////////////////////////////////////////
  // Memory configuration status reporter
  //////////////////////////////////////////////////////////////////////////////
  inline void memories()
  {
    printf(" Memory alignment        : %d\n", NT2_CONFIG_ALIGNMENT );
    #if defined(NT2_CONFIG_SUPPORT_POSIX_MEMALIGN)
      puts(" Memory allocation       : posix_memalign");
    #elif defined(_MSC_VER)
      puts(" Memory allocation       : _aligned_malloc");
    #else
      puts(" Memory allocation       : pointer stashing");
    #endif
    puts("");
  }

  NT2_REGISTER_STATUS(memories);
} }

#endif
