/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONFIG_OS_HPP_INCLUDED
#define NT2_SDK_CONFIG_OS_HPP_INCLUDED

#include <nt2/sdk/config/bootstrap.hpp>
#include <nt2/sdk/config/details/boost.hpp>
#include <nt2/sdk/config/details/reporter.hpp>

////////////////////////////////////////////////////////////////////////////////
// Architecture configuration headers
// Defines architecture symbols for architecture related variation point.
////////////////////////////////////////////////////////////////////////////////
#include <boost/version.hpp>
#include <boost/config.hpp>

//#include <nt2/extensions/sdk/config/os.hpp>
#include <nt2/sdk/config/os/nix.hpp>
#include <nt2/sdk/config/os/windows.hpp>
#include <nt2/sdk/config/os/macos.hpp>
#include <nt2/sdk/config/os/none.hpp>

namespace nt2 { namespace config
{
  //////////////////////////////////////////////////////////////////////////////
  // Status header reporter - Head for the reporter list
  //////////////////////////////////////////////////////////////////////////////
  static void os()
  {
    puts(" Operating System        : " NT2_OS_STRING );
  }

  NT2_REGISTER_STATUS(os);
} }

#endif
