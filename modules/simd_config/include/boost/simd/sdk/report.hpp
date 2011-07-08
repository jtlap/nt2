/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_REPORT_HPP_INCLUDED
#define BOOST_SIMD_SDK_REPORT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Main report header
// TOFO: Documentation: http://nt2.lri.fr/sdk/report.html
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Internal BOOST_SIMD configuration report
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/config/os/report.hpp>
#include <boost/simd/sdk/config/arch/report.hpp>
#include <boost/simd/sdk/config/compiler/report.hpp>
#include <boost/simd/sdk/config/software.hpp>

namespace boost { namespace simd { namespace config
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

  BOOST_SIMD_REGISTER_STATUS(sdk);
} } }

////////////////////////////////////////////////////////////////////////////////
// SDK configuration report
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/simd/report.hpp>
#include <boost/simd/sdk/memory/report.hpp>
#include <boost/simd/sdk/error/report.hpp>

#endif
