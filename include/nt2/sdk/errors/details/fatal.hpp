/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_ERRORS_DETAILS_FATAL_HPP_INCLUDED
#define NT2_SDK_ERRORS_DETAILS_FATAL_HPP_INCLUDED

#include <nt2/sdk/errors/details/message.hpp>
#include <nt2/sdk/errors/details/warning.hpp>
#include <nt2/sdk/errors/details/exception.hpp>

namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // error infos type
  //////////////////////////////////////////////////////////////////////////////
  namespace details { NT2_ERROR_INFO(error_,char const*); }

  //////////////////////////////////////////////////////////////////////////////
  // error_exception is defined if warning are upgraded to errors
  //////////////////////////////////////////////////////////////////////////////
  struct NT2_EXCEPTION_BASE(error_exception)
  {
    #if !defined(BOOST_NO_EXCEPTIONS)
    virtual void display(std::ostream& os) const throw()
    {
      os  << "FATAL ERROR: "
          << *boost::get_error_info<details::error_>(*this) << "\n";
    }
    #endif
  };
}

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Forward a fatal error string to the proper default or user-defined logger
  //////////////////////////////////////////////////////////////////////////////
  inline void emit_fatal( const char* msg )
  {
    #if !defined(NT2_FATAL_HANDLER)
    fprintf(stderr,"%s\n",msg);
    #else
    nt2::ext::emit_fatal(msg);
    #endif
  }

  template<class String>
  inline void emit_fatal( String const& msg ) { emit_fatal(msg.c_str()); }
} }

#define NT2_EMIT_FATAL(Message)                             \
nt2::details::emit_fatal(                                   \
    nt2::details::message ( "NT2 FATAL ERROR"               \
                          , Message,BOOST_CURRENT_FUNCTION  \
                          , __FILE__,__LINE__)              \
                          )                                 \
/**/

#endif
