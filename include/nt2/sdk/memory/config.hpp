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

namespace nt2 { namespace config
{
  //////////////////////////////////////////////////////////////////////////////
  // Memory configuration status reporter
  //////////////////////////////////////////////////////////////////////////////
  static void memories()
  {
    printf(" Memory alignment        : %d\n\n", NT2_CONFIG_ALIGNMENT );
  }

  NT2_REGISTER_STATUS(memories);
} }

#endif
