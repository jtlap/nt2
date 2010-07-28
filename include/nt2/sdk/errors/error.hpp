/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_ERRORS_ERROR_HPP_INCLUDED
#define NT2_SDK_ERRORS_ERROR_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Error Reporting System
// Documentation: http://nt2.lri.fr/sdk/errors/error.html
// Documentation: http://nt2.lri.fr/sdk/errors/config.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/errors/details/error.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <nt2/sdk/errors/details/warning.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

////////////////////////////////////////////////////////////////////////////////
// No exception means no error unless they got requalified
////////////////////////////////////////////////////////////////////////////////
#include <boost/config.hpp>
#if defined(BOOST_NO_EXCEPTIONS)
#if defined( NT2_VERBOSE )
#warning Exceptions globally disabled
#endif
#define NT2_DISABLE_ERROR
#endif

////////////////////////////////////////////////////////////////////////////////
// Verbose report
////////////////////////////////////////////////////////////////////////////////
#if defined( NT2_VERBOSE )
  #if defined(NT2_ERROR_AS_WARNING)
//    #warning Errors requalified as warnings
  #elif defined(NT2_ERROR_AS_FAILURE)
//    #warning Errors requalified as failures
  #elif defined(NT2_CUSTOM_ERROR)
    //#warning Errors handled by user
  #elif defined(NT2_DISABLE_ERROR)
    //#warning Errors disabled
  #else
    //#warning Errors enabled
  #endif
#endif

////////////////////////////////////////////////////////////////////////////////
// Configuration string
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_ERROR_AS_WARNING)
  #define NT2_ERROR_CONFIG_STRING "enabled as warnings"
#elif defined(NT2_ERROR_AS_FAILURE)
  #define NT2_ERROR_CONFIG_STRING "enabled as failures"
#elif defined(NT2_CUSTOM_ERROR)
  #define NT2_ERROR_CONFIG_STRING "user-defined"
#elif defined(NT2_DISABLE_ERROR)
  #if defined(BOOST_NO_EXCEPTIONS)
  #define NT2_ERROR_CONFIG_STRING "globally disabled"
  #else
  #define NT2_ERROR_CONFIG_STRING "disabled"
  #endif
#else
  #if defined(NT2_DISABLE_DAIGNOSTICS)
  #define NT2_ERROR_CONFIG_STRING "enabled without diagnostic"
  #else
  #define NT2_ERROR_CONFIG_STRING "enabled"
  #endif
#endif

////////////////////////////////////////////////////////////////////////////////
// Option to set exit code for failure error
////////////////////////////////////////////////////////////////////////////////
#ifndef NT2_ERROR_EXIT_CODE
#define NT2_ERROR_EXIT_CODE EXIT_FAILURE
#endif

////////////////////////////////////////////////////////////////////////////////
// Option to set exit code for failure
////////////////////////////////////////////////////////////////////////////////
#ifndef NT2_ERROR_EXIT_CODE
  #define NT2_ERROR_EXIT_CODE EXIT_FAILURE
#endif

#include <sstream>
#include <nt2/sdk/errors/details/exception.hpp>

////////////////////////////////////////////////////////////////////////////////
// Errors can be requalified as warnings
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_ERROR_AS_WARNING)
#define NT2_ERROR(EXP)                    \
{                                         \
  std::ostringstream s; (EXP).display(s); \
  do{ NT2_EMIT_WARNING(s.str().c_str());  \
    } while(0);                           \
}                                         \
/**/

////////////////////////////////////////////////////////////////////////////////
// errors can be requalified as failures
////////////////////////////////////////////////////////////////////////////////
#elif defined(NT2_ERROR_AS_FAILURE)
#define NT2_ERROR(EXP)                    \
{                                         \
  std::ostringstream s; (EXP).display(s); \
  do{ NT2_EMIT_FAILURE(s.str().c_str());  \
      exit(NT2_ERROR_EXIT_CODE);          \
    } while(0);                           \
}                                         \
/**/

////////////////////////////////////////////////////////////////////////////////
// Enabled errors
////////////////////////////////////////////////////////////////////////////////
#elif !defined(NT2_DISABLE_ERROR)
#define NT2_ERROR(EXP) BOOST_THROW_EXCEPTION( (EXP) ) \
/**/

////////////////////////////////////////////////////////////////////////////////
// Disabled errors
////////////////////////////////////////////////////////////////////////////////
#else
#define NT2_ERROR(EXP)
#endif

#endif
