/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_NT2_SDK_ERRORS_FAILURE_HPP_INCLUDED
#define NT2_NT2_SDK_ERRORS_FAILURE_HPP_INCLUDED

#include <nt2/sdk/errors/details/warning.hpp>
#include <nt2/sdk/errors/details/failure.hpp>

////////////////////////////////////////////////////////////////////////////////
// Verbose report
////////////////////////////////////////////////////////////////////////////////
#if defined( NT2_VERBOSE )
  #if defined(NT2_FAILURE_AS_WARNING)
    #warning Failures requalified as warnings
  #elif defined(NT2_FAILURE_AS_ERROR)
    #warning Failures requalified as errors
  #elif defined(NT2_CUSTOM_FAILURE)
    #warning Failures handled by user
  #elif defined( NT2_DISABLE_FAILURE)
    #warning Failures disabled
  #else
    #warning Failures enabled
  #endif
#endif

////////////////////////////////////////////////////////////////////////////////
// Configuration string
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_FAILURE_AS_WARNING)
  #define NT2_FAILURE_CONFIG_STRING "enabled as warnings"
#elif defined(NT2_FAILURE_AS_ERROR)
  #define NT2_FAILURE_CONFIG_STRING "enabled as errors"
#elif defined(NT2_CUSTOM_FAILURE)
  #define NT2_FAILURE_CONFIG_STRING "user-defined"
#elif defined( NT2_DISABLE_FAILURE)
  #define NT2_FAILURE_CONFIG_STRING "disabled"
#else
  #define NT2_FAILURE_CONFIG_STRING "enabled"
#endif

////////////////////////////////////////////////////////////////////////////////
// Option to set exit code for failure
////////////////////////////////////////////////////////////////////////////////
#ifndef NT2_FAILURE_EXIT_CODE
  #define NT2_FAILURE_EXIT_CODE EXIT_FAILURE
#endif

////////////////////////////////////////////////////////////////////////////////
// Failures can be requalified as warnings
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_FAILURE_AS_WARNING)
#define NT2_FAILURE(COND,MSG)                       \
do { if(!(COND)) NT2_EMIT_WARNING(MSG); } while(0)  \
/**/

////////////////////////////////////////////////////////////////////////////////
// Failures can be requalified as errors
////////////////////////////////////////////////////////////////////////////////
#elif defined(NT2_FAILURE_AS_ERROR)
#define NT2_FAILURE(COND,MSG)                                               \
do  { if(!(COND))                                                           \
      NT2_ERROR( nt2::failure_exception, ((nt2::details::failure_,MSG)) );  \
    } while(0)                                                              \
/**/

////////////////////////////////////////////////////////////////////////////////
// Enabled failures
////////////////////////////////////////////////////////////////////////////////
#elif !defined(NT2_DISABLE_FAILURE)
#define NT2_FAILURE(COND,MSG)                                                   \
do { if(!(COND)) NT2_EMIT_FAILURE(MSG); exit(NT2_FAILURE_EXIT_CODE); } while(0) \
/**/

////////////////////////////////////////////////////////////////////////////////
// Disabled failures
////////////////////////////////////////////////////////////////////////////////
#else
#define NT2_FAILURE(COND,MSG)
#endif

#endif
