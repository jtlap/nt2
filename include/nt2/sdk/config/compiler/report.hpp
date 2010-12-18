/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONFIG_COMPILER_REPORT_HPP_INCLUDED
#define NT2_SDK_CONFIG_COMPILER_REPORT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Architecture configuration headers
// Defines architecture symbols for architecture related variation point.
// Documentation: http://nt2.lri.fr/sdk/config/compiler.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/config/compiler.hpp>
#include <nt2/sdk/config/details/reporter.hpp>

namespace nt2 { namespace config
{
  //////////////////////////////////////////////////////////////////////////////
  // Status header reporter - Head for the reporter list
  //////////////////////////////////////////////////////////////////////////////
  inline void compiler()
  {
    puts(" Compiler                : " NT2_COMPILER_STRING);
    puts(" Rvalue references       : "
    #if   defined(BOOST_NO_RVALUE_REFERENCES)
          "unsupported"
    #else
          "supported"
    #endif
        );

    puts(" Variadic templates      : "
    #if   defined(BOOST_NO_VARIADIC_TEMPLATES)
          "unsupported"
    #else
          "supported"
    #endif
        "\n"
        );
  }

  NT2_REGISTER_STATUS(compiler);
} }

#endif
