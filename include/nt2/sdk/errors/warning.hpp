/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_ERRORS_WARNING_HPP_INCLUDED
#define NT2_SDK_ERRORS_WARNING_HPP_INCLUDED

#include <nt2/sdk/errors/details/warning.hpp>

////////////////////////////////////////////////////////////////////////////////
// Verbose report
////////////////////////////////////////////////////////////////////////////////
#if defined( NT2_VERBOSE )
  #if defined(NT2_WARNING_AS_FAILURE)
    #warning Warnings requalified as failures
  #elif defined(NT2_WARNING_AS_ERROR)
    #warning Warnings requalified as errors
  #elif defined(NT2_CUSTOM_WARNING)
    #warning Warnings handled by user
  #elif defined( NT2_DISABLE_WARNING)
    #warning Warnings disabled
  #else
    #warning Warnings enabled
  #endif
#endif

////////////////////////////////////////////////////////////////////////////////
// Configuration string
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_WARNING_AS_FAILURE)
  #define NT2_WARNING_CONFIG_STRING "enabled as failures"
#elif defined(NT2_WARNING_AS_ERROR)
  #define NT2_WARNING_CONFIG_STRING "enabled as errors"
#elif defined(NT2_CUSTOM_WARNING)
  #define NT2_WARNING_CONFIG_STRING "user-defined"
#elif defined( NT2_DISABLE_WARNING)
  #define NT2_WARNING_CONFIG_STRING "disabled"
#else
  #define NT2_WARNING_CONFIG_STRING "enabled"
#endif

////////////////////////////////////////////////////////////////////////////////
// Warning can be requalified as Failure
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_WARNING_AS_FAILURE)

  //////////////////////////////////////////////////////////////////////////////
  // Option to set exit code for failure warning
  //////////////////////////////////////////////////////////////////////////////
  #ifndef NT2_WARNING_EXIT_CODE
    #define NT2_WARNING_EXIT_CODE EXIT_FAILURE
  #endif

  //////////////////////////////////////////////////////////////////////////////
  // Fatal warning display an error then exit
  //////////////////////////////////////////////////////////////////////////////
  #include <nt2/sdk/errors/details/fatal.hpp>

  #define NT2_WARNING(MSG)                                          \
  do { NT2_EMIT_FATAL(MSG); exit(NT2_WARNING_EXIT_CODE); } while(0) \

////////////////////////////////////////////////////////////////////////////////
// Warning can be requalified as Errors
////////////////////////////////////////////////////////////////////////////////
#elif defined(NT2_WARNING_AS_ERROR)
#define NT2_WARNING(MSG)                                            \
NT2_ERROR( nt2::warning_exception, ((nt2::details::warning_,MSG)) ) \
/**/

////////////////////////////////////////////////////////////////////////////////
// Regular warning
////////////////////////////////////////////////////////////////////////////////
#elif !defined(NT2_DISABLE_WARNING)
#include <boost/current_function.hpp>

#define NT2_WARNING(MSG) NT2_EMIT_WARNING(MSG)

////////////////////////////////////////////////////////////////////////////////
// Disabled warnings
////////////////////////////////////////////////////////////////////////////////
#else
#define NT2_WARNING(MSG)
#endif

#endif
