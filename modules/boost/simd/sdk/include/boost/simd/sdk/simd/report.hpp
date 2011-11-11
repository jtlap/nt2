/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_REPORT_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_REPORT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Memory config header
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/simd/sdk/config/details/reporter.hpp>

namespace boost { namespace simd { namespace config
{
  //////////////////////////////////////////////////////////////////////////////
  // SIMD configuration status reporter
  //////////////////////////////////////////////////////////////////////////////
  inline void simd()
  {
    #if defined(BOOST_SIMD_DETECTED)
    puts(" SIMD support            : enabled");
    puts(" Active extension        : " BOOST_SIMD_STRING );
    puts(" Available extensions    : " BOOST_SIMD_STRING_LIST );
    #else
    puts(" SIMD support            : disabled");
    puts(" Active extension        : none"    );
    puts(" Available extensions    : none"    );
    #endif

    puts("");
  }

  BOOST_SIMD_REGISTER_STATUS(simd);
} } }

#endif
