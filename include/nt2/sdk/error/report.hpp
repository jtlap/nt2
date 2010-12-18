//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_ERROR_REPORT_HPP_INCLUDED
#define NT2_SDK_ERROR_REPORT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Memory config header
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/config.hpp>
#include <nt2/sdk/error/debug.hpp>

namespace nt2 { namespace config
{
  //////////////////////////////////////////////////////////////////////////////
  // Error configuration status reporter
  //////////////////////////////////////////////////////////////////////////////
  static void errors()
  {
    #if defined(NT2_RELEASE)
    puts(" Compilation mode        : release");
    #elif defined(NT2_DEBUG)
    puts(" Compilation mode        : debug");
    #else
    puts(" Compilation mode        : normal");
    #endif

    #if defined(NT2_DISABLE_ASSERTS)
    puts(" Assertion Failures      : disabled");
    #elif defined(NT2_ASSERTS_AS_EXCEPTIONS)
    puts(" Assertion Failures      : as exceptions");
    #else
    puts(" Assertion Failures      : enabled");
    #endif

    #if defined(NT2_USE_CONCEPTS)
    puts(" Concepts checks         : enabled");
    #else
    puts(" Concepts checks         : disabled");
    #endif
    puts("");
  }

  NT2_REGISTER_STATUS(errors);
} }

#endif
