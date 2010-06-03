/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONFIG_ARCH_HPP_INCLUDED
#define NT2_SDK_CONFIG_ARCH_HPP_INCLUDED

#include <nt2/sdk/config/bootstrap.hpp>

////////////////////////////////////////////////////////////////////////////////
// Architecture configuration headers
// Defines architecture symbols for compile-time switch over architecture
// related variation point.
// Documentation: reference/sdk/config/architecture.rst
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

//  #include <nt2/extensions/arch.hpp>
  #include <nt2/sdk/config/arch/powerpc.hpp>
  #include <nt2/sdk/config/arch/x86.hpp>
  #include <nt2/sdk/config/arch/ia64.hpp>
  #include <nt2/sdk/config/arch/none.hpp>

//#include <nt2/support/config/arch/spec.hpp>
//#include <nt2/support/config/arch/endian.hpp>
#endif

#endif
