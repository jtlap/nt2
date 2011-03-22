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
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/config/types.hpp>

////////////////////////////////////////////////////////////////////////////////
// Detect if we can use any pre-existing aligned memory allocation function
////////////////////////////////////////////////////////////////////////////////
#if (     (defined _GNU_SOURCE)                                   \
      ||  ((defined _XOPEN_SOURCE) && (_XOPEN_SOURCE >= 600))     \
    )                                                             \
 && (defined _POSIX_ADVISORY_INFO) && (_POSIX_ADVISORY_INFO > 0)
  #include <cstdlib>
  #include <cstring>
  #define NT2_CONFIG_SUPPORT_POSIX_MEMALIGN
#endif

////////////////////////////////////////////////////////////////////////////////
// Small byte typedef for memory components
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace memory
{
  typedef nt2::uint8_t byte;
} }

#endif
