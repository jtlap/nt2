/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONFIG_ARCH_REPORT_HPP_INCLUDED
#define NT2_SDK_CONFIG_ARCH_REPORT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Architecture configuration headers report
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/config/arch.hpp>
#include <nt2/sdk/config/details/reporter.hpp>

namespace nt2 { namespace config
{
  //////////////////////////////////////////////////////////////////////////////
  // Status header reporter - Head for the reporter list
  //////////////////////////////////////////////////////////////////////////////
  inline void architecture()
  {
    puts(" CPU Architecture        : " NT2_ARCH_STRING "\n");
  }

  NT2_REGISTER_STATUS(architecture);
} }

#endif
