/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_NT2_SDK_CONFIG_CONFIG_HPP_INCLUDED
#define NT2_NT2_SDK_CONFIG_CONFIG_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Status function and verbose warning
// Defines function for accessing run-time information about compile-time
// parameters.
// Documentation: reference/sdk/config/flags.rst
// Documentation: reference/sdk/config/function.rst
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//Includes NT2 configuration files
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/config/os.hpp>
#include <nt2/sdk/config/arch.hpp>
#include <nt2/sdk/config/version.hpp>
#include <nt2/sdk/config/compiler.hpp>
#include <nt2/sdk/config/threading.hpp>

////////////////////////////////////////////////////////////////////////////////
// Module configuration
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/simd/extensions.hpp>

////////////////////////////////////////////////////////////////////////////////
// Setup some additional string macros
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_USE_EXCEPTION) && !defined(BOOST_NO_EXCEPTIONS)
  #define NT2_EXCEPTION_STRING  "activated"
#else
  #define NT2_EXCEPTION_STRING  "desactivated"
#endif
#if defined(NT2_USE_ASSERT) && !defined(BOOST_DISABLE_ASSERTS)
  #define NT2_ASSERT_STRING  "activated"
#else
  #define NT2_ASSERT_STRING  "desactivated"
#endif
#if defined(NT2_USE_CONCEPTS)
  #define NT2_CONCEPT_STRING  "activated"
#else
  #define NT2_CONCEPT_STRING  "desactivated"
#endif
#if defined(NT2_USE_OPENMP)
  #define NT2_OPENMP_STRING  "activated"
#else
  #define NT2_OPENMP_STRING  "desactivated"
#endif
#if defined(NT2_VERBOSE)
  #define NT2_VERBOSE_STRING  "activated"
#else
  #define NT2_VERBOSE_STRING  "desactivated"
#endif

////////////////////////////////////////////////////////////////////////////////
// VERBOSE Mode informations on additional config macros
////////////////////////////////////////////////////////////////////////////////
#ifdef NT2_VERBOSE
  #if defined(NT2_USE_EXCEPTION) && !defined(BOOST_NO_EXCEPTIONS)
    #warning NT2 Configuration: Exception enabled
  #elif defined(NT2_USE_EXCEPTION) && defined(BOOST_NO_EXCEPTIONS)
    #warning NT2 Configuration: Exception disabled via BOOST_NO_EXCEPTIONS
  #endif
  #if defined(NT2_USE_ASSERT) && !defined(BOOST_DISABLE_ASSERTS)
    #warning NT2 Configuration: Assertion enabled
  #endif
  #if defined(NT2_USE_ASSERT) && !defined(BOOST_DISABLE_ASSERTS)
    #warning NT2 Configuration: Assertion disabled via BOOST_DISABLE_ASSERTS
  #endif
  #if defined(NT2_USE_CONCEPTS)
    #warning NT2 Configuration: Concepts checking activated
  #endif
#endif

namespace nt2
{
  namespace config
  {
    static inline const char*  os()              { return NT2_OS_STRING;       }
    static inline const char*  compiler()        { return NT2_COMPILER_STRING; }
    static inline const char*  architecture()    { return NT2_ARCH_STRING;     }

    static inline const char* status()
    {
      static const char cfg[] =
      "/*************************************************************************\\\n"
      "|                    NT2 version " PACKAGE_VERSION
      " release "       NT2_VERSION_CODENAME
                                                            "                    |\n"
      "|*************************************************************************|\n"
      "|                          Compilation Settings                           |\n"
      "\\*************************************************************************/\n"
      " CPU Architecture        : " NT2_ARCH_STRING                               "\n"
      " Operating System        : " NT2_OS_STRING                                 "\n"
      " Compiler                : " NT2_COMPILER_STRING                           "\n"
      " Boost libraries version : " BOOST_LIB_VERSION                             "\n"
      "/*************************************************************************\\\n"
      "|                          Hardware Settings                              |\n"
      "\\*************************************************************************/\n"
      " SIMD support            : " NT2_SIMD_STRING                               "\n"
      " OpenMP support          : " NT2_OPENMP_STRING                             "\n"
      "/*************************************************************************\\\n"
      "|                              User Settings                              |\n"
      "\\*************************************************************************/\n"
      " Verbose mode     : " NT2_VERBOSE_STRING                    "\n"
      " Exceptions       : " NT2_EXCEPTION_STRING                  "\n"
      " Assertions       : " NT2_ASSERT_STRING                     "\n"
      " Concepts checks  : " NT2_CONCEPT_STRING                    "\n";

      return cfg;
    }
  }
}
#endif
