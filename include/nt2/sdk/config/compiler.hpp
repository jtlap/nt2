/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONFIG_COMPILER_HPP_INCLUDED
#define NT2_SDK_CONFIG_COMPILER_HPP_INCLUDED

#include <nt2/sdk/config/bootstrap.hpp>
#include <nt2/sdk/config/details/boost.hpp>
#include <nt2/sdk/config/details/reporter.hpp>

////////////////////////////////////////////////////////////////////////////////
// Architecture configuration headers
// Defines architecture symbols for architecture related variation point.
////////////////////////////////////////////////////////////////////////////////
#include <boost/version.hpp>
#include <boost/config.hpp>

#include <nt2/sdk/config/compiler/gcc_xml.hpp>
// #include <nt2/extensions/sdk/config/compiler.hpp>
#include <nt2/sdk/config/compiler/gcc.hpp>
#include <nt2/sdk/config/compiler/visualc.hpp>
#include <nt2/sdk/config/compiler/none.hpp>

namespace nt2 { namespace config
{
  //////////////////////////////////////////////////////////////////////////////
  // Status header reporter - Head for the reporter list
  //////////////////////////////////////////////////////////////////////////////
  static void compiler()
  {
    puts(" Compiler                : " NT2_COMPILER_STRING);
    puts(" Rvalue references       : "
    #if   defined(BOOST_NO_RVALUE_REFERENCES)
          "unsupported"
    #else
          "supported"
    #endif
        );

    puts(" Variadic templates       : "
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
