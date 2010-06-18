/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_NT2_SDK_ERRORS_DETAILS_ERROR_HPP_INCLUDED
#define NT2_NT2_SDK_ERRORS_DETAILS_ERROR_HPP_INCLUDED

#include <boost/exception/all.hpp>
#include <nt2/sdk/errors/details/warning.hpp>

////////////////////////////////////////////////////////////////////////////////
// Option to set exit code for fatal error
////////////////////////////////////////////////////////////////////////////////
#ifndef NT2_ERROR_AS_FATAL_EXIT_CODE
#define NT2_ERROR_AS_FATAL_EXIT_CODE EXIT_FAILURE
#endif

////////////////////////////////////////////////////////////////////////////////
// Verbose configuration
////////////////////////////////////////////////////////////////////////////////
#if defined( NT2_VERBOSE )
  #if defined( NT2_ERROR_AS_FATAL )
  #warning NT2 Errors requalified as fatal errors
  #elif defined(NT2_ERROR_AS_WARNING)
  #warning NT2 Errors requalified as warning
  #elif defined(NT2_USE_CUSTOM_ERROR_HANDLER)
  #warning NT2 Errors uses custom handler
  #else
  #warning NT2 Errors disabled
  #endif
#endif

////////////////////////////////////////////////////////////////////////////////
// When exception are disabled via -fno-exceptions, one can specify how to
// handle exception all together
////////////////////////////////////////////////////////////////////////////////
#if defined(BOOST_NO_EXCEPTIONS)
namespace boost
{
  void throw_exception( std::exception const & e )
  {
    ////////////////////////////////////////////////////////////////////////////
    // When error becomes fatal, log+exit
    ////////////////////////////////////////////////////////////////////////////
    #if defined( NT2_ERROR_AS_FATAL )
    #define NT2_ERROR_CONFIG_STRING "enabled as fatal errors"
    nt2::details::emit_warning( e.what() );
    exit(NT2_ERROR_AS_FATAL_EXIT_CODE);
    ////////////////////////////////////////////////////////////////////////////
    // When error becomes warning, log
    ////////////////////////////////////////////////////////////////////////////
    #elif defined(NT2_ERROR_AS_WARNING)
    #define NT2_ERROR_CONFIG_STRING "enabled as warnings"
    nt2::details::emit_warning( e.what() );
    ////////////////////////////////////////////////////////////////////////////
    // If not use custom handler if possible
    ////////////////////////////////////////////////////////////////////////////
    #elif defined(NT2_USE_CUSTOM_ERROR_HANDLER)
    #define NT2_ERROR_CONFIG_STRING "user-defined"
    nt2::ext::throw_exception(e);
    #else
    #define NT2_ERROR_CONFIG_STRING "disabled"
    #endif
    ////////////////////////////////////////////////////////////////////////////
    // If not, error are disabled
    ////////////////////////////////////////////////////////////////////////////
  }
}

#endif

#endif
