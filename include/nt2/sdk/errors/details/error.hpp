/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_ERRORS_DETAILS_ERROR_HPP_INCLUDED
#define NT2_SDK_ERRORS_DETAILS_ERROR_HPP_INCLUDED

#include <string>
#include <boost/exception/all.hpp>
#include <nt2/sdk/errors/details/warning.hpp>

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
    nt2::details::emit_warning( std::string(e.what()) );
    exit(NT2_ERROR_EXIT_CODE);
    ////////////////////////////////////////////////////////////////////////////
    // When error becomes warning, log
    ////////////////////////////////////////////////////////////////////////////
    #elif defined(NT2_ERROR_AS_WARNING)
    nt2::details::emit_warning( nt2::sys::string(e.what()) );
    ////////////////////////////////////////////////////////////////////////////
    // If not use custom handler if possible
    ////////////////////////////////////////////////////////////////////////////
    #elif defined(NT2_ERROR_HANDLER)
    nt2::ext::emit_error(e);
    #endif
    ////////////////////////////////////////////////////////////////////////////
    // If not, error are disabled
    ////////////////////////////////////////////////////////////////////////////
  }
}
#endif

#endif
