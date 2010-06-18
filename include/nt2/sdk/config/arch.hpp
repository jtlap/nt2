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
#include <nt2/sdk/config/details/boost.hpp>
#include <nt2/sdk/config/details/reporter.hpp>

////////////////////////////////////////////////////////////////////////////////
// Architecture configuration headers
// Defines architecture symbols for architecture related variation point.
////////////////////////////////////////////////////////////////////////////////
#include <boost/version.hpp>
#include <boost/config.hpp>

//  #include <nt2/extensions/sdk/config/arch.hpp>
#include <nt2/sdk/config/arch/powerpc.hpp>
#include <nt2/sdk/config/arch/x86.hpp>
#include <nt2/sdk/config/arch/ia64.hpp>
#include <nt2/sdk/config/arch/none.hpp>

//#include <nt2/support/config/arch/spec.hpp>
//#include <nt2/support/config/arch/endian.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Status header reporter - Head for the reporter list
  //////////////////////////////////////////////////////////////////////////////
  static void architecture()
  {
    puts(" CPU Architecture        : " NT2_ARCH_STRING "\n");
  }

  NT2_REGISTER_STATUS(architecture);
} }

#endif
