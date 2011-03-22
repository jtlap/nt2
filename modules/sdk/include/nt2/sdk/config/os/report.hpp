/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONFIG_OS_REPORT_HPP_INCLUDED
#define NT2_SDK_CONFIG_OS_REPORT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// OS reporting
// TODO: Documentation: http://nt2.lri.fr/doc/build/html/sdk/config/platform.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/config/os.hpp>
#include <nt2/sdk/config/details/reporter.hpp>

namespace nt2 { namespace config
{
  //////////////////////////////////////////////////////////////////////////////
  // Status header reporter - Head for the reporter list
  //////////////////////////////////////////////////////////////////////////////
  inline void os()
  {
    puts(" Operating System        : " NT2_OS_STRING );
  }

  NT2_REGISTER_STATUS(os);
} }

#endif
