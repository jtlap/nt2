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

#include <nt2/sdk/config/configure.hpp>

////////////////////////////////////////////////////////////////////////////////
// OS configuration headers
// Defines OS specific symbols for compile-time switch over OS related
// variation points.
// Documentation: reference/sdk/config/platform.rst
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Performs sanity check - We never knows ...
////////////////////////////////////////////////////////////////////////////////
#if !defined(NT2_HAVE_BOOST)
  #error NT2 Configuration Error: No Boost library detected
#else
  //////////////////////////////////////////////////////////////////////////////
  // Includes BOOST configuration files
  //////////////////////////////////////////////////////////////////////////////
  #include <boost/version.hpp>
  #include <boost/config.hpp>

  #include <nt2/extensions/os.hpp>
  #include <nt2/sdk/config/os/nix.hpp>
  #include <nt2/sdk/config/os/windows.hpp>
  #include <nt2/sdk/config/os/macos.hpp>
  #include <nt2/sdk/config/os/none.hpp>
#endif

#endif
