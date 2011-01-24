/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_REPORT_HPP_INCLUDED
#define NT2_SDK_REPORT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Main report header
// TOFO: Documentation: http://nt2.lri.fr/sdk/report.html
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Internal NT2 configuration report
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/config/os/report.hpp>
#include <nt2/sdk/config/arch/report.hpp>
#include <nt2/sdk/config/compiler/report.hpp>
#include <nt2/sdk/config/software.hpp>

namespace nt2 { namespace config
{
  //////////////////////////////////////////////////////////////////////////////
  // Memory configuration status reporter
  //////////////////////////////////////////////////////////////////////////////
  inline void sdk()
  {
    puts("/****************************************************************\\");
    puts("|                          SDK Settings                          |");
    puts("\\****************************************************************/");
  }

  NT2_REGISTER_STATUS(sdk);
} }

////////////////////////////////////////////////////////////////////////////////
// SDK configuration report
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/simd/report.hpp>
#include <nt2/sdk/memory/report.hpp>
#include <nt2/sdk/error/report.hpp>

////////////////////////////////////////////////////////////////////////////////
// External NT2 configuration report
////////////////////////////////////////////////////////////////////////////////
#include <nt2/extension/sdk/report.hpp>

#endif
