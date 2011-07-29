/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_CONFIG_OS_REPORT_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_OS_REPORT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// OS reporting
// TODO: Documentation: http://nt2.lri.fr/doc/build/html/sdk/config/platform.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/config/os.hpp>
#include <boost/simd/sdk/config/details/reporter.hpp>

namespace boost { namespace simd { namespace config
{
  //////////////////////////////////////////////////////////////////////////////
  // Status header reporter - Head for the reporter list
  //////////////////////////////////////////////////////////////////////////////
  inline void os()
  {
    puts(" Operating System        : " BOOST_SIMD_OS );
  }

  BOOST_SIMD_REGISTER_STATUS(os);
} } }

#endif
