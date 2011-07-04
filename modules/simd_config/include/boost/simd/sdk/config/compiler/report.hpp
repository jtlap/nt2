/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_CONFIG_COMPILER_REPORT_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_COMPILER_REPORT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Architecture configuration headers
// Defines architecture symbols for architecture related variation point.
// Documentation: http://nt2.lri.fr/sdk/config/compiler.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/config/compiler.hpp>
#include <boost/simd/sdk/config/details/reporter.hpp>

namespace boost { namespace simd { namespace config
{
  //////////////////////////////////////////////////////////////////////////////
  // Status header reporter - Head for the reporter list
  //////////////////////////////////////////////////////////////////////////////
  inline void compiler()
  {
    puts(" Compiler                : " BOOST_SIMD_COMPILER);
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

  BOOST_SIMD_REGISTER_STATUS(compiler);
} } }

#endif
