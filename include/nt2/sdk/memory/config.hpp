/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_CONFIG_HPP_INCLUDED
#define NT2_SDK_MEMORY_CONFIG_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Memory config header
// TODO: Documentation: http://nt2.lri.fr/sdk/memory/config.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/config.hpp>
#include <nt2/sdk/config/types.hpp>

#if (     (defined _GNU_SOURCE)                                   \
      ||  ((defined _XOPEN_SOURCE) && (_XOPEN_SOURCE >= 600))     \
    )                                                             \
 && (defined _POSIX_ADVISORY_INFO) && (_POSIX_ADVISORY_INFO > 0)
  #include <cstdlib>
  #include <cstring>
  #define NT2_CONFIG_SUPPORT_POSIX_MEMALIGN
#endif

namespace nt2 { namespace memory
{
  // Small byte typedef for memory components
  typedef uint8_t byte;
} }

namespace nt2 { namespace config
{
  //////////////////////////////////////////////////////////////////////////////
  // Memory configuration status reporter
  //////////////////////////////////////////////////////////////////////////////
  static void memories()
  {
    printf(" Memory alignment        : %d\n", NT2_CONFIG_ALIGNMENT );
    #if defined(NT2_CONFIG_SUPPORT_POSIX_MEMALIGN)
      puts(" Memory allocation       : posix_memalign\n\n");
    #elif defined(_MSC_VER)
      puts(" Memory allocation       : _aligned_malloc\n\n");
    #else
      puts(" Memory allocation       : pointer stashing\n\n");
    #endif
  }

  NT2_REGISTER_STATUS(memories);
} }

#endif
