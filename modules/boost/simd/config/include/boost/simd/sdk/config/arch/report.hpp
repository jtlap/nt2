/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_CONFIG_ARCH_REPORT_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_ARCH_REPORT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Architecture configuration headers report
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/config/arch.hpp>
#include <boost/simd/sdk/config/details/reporter.hpp>

namespace boost { namespace simd { namespace config
{
  //////////////////////////////////////////////////////////////////////////////
  // Status header reporter - Head for the reporter list
  //////////////////////////////////////////////////////////////////////////////
  inline void architecture()
  {
    puts(" CPU Architecture        : " BOOST_SIMD_ARCH "\n");
  }

  BOOST_SIMD_REGISTER_STATUS(architecture);
} } }

#endif
