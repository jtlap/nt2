/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_REPORT_HPP_INCLUDED
#define NT2_SDK_MEMORY_REPORT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Memory config header
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/simd/extensions.hpp>
#include <nt2/sdk/config/details/reporter.hpp>

namespace nt2 { namespace config
{
  //////////////////////////////////////////////////////////////////////////////
  // SIMD configuration status reporter
  //////////////////////////////////////////////////////////////////////////////
  inline void simd()
  {
    #if defined(NT2_SIMD_DETECTED)
    puts(" SIMD support            : enabled");
    puts(" Active extension        : " NT2_SIMD_STRING );
    puts(" Available extensions    : " NT2_SIMD_STRING_LIST );
    #else
    puts(" SIMD support            : disabled");
    puts(" Active extension        : none"    );
    puts(" Available extensions    : none"    );
    #endif

    puts("");
  }

  NT2_REGISTER_STATUS(simd);
} }

#endif
