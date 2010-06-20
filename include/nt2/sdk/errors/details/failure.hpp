/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_ERRORS_DETAILS_FAILURE_HPP_INCLUDED
#define NT2_SDK_ERRORS_DETAILS_FAILURE_HPP_INCLUDED

#include <nt2/sdk/errors/details/message.hpp>
//#include <nt2/sdk/errors/details/exception.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Forward a fatal error string to the proper default or user-defined logger
  //////////////////////////////////////////////////////////////////////////////
  inline void emit_failure( sys::string const& msg )
  {
    #if !defined(NT2_FATAL_HANDLER)
    fprintf(stderr,"%s\n",msg.c_str());
    #else
    nt2::ext::emit_failure(msg.c_str());
    #endif
  }

} }

#define NT2_EMIT_FAILURE(Message)                           \
nt2::details::emit_failure(                                   \
    nt2::details::message ( "NT2 FAILURE"                   \
                          , Message,BOOST_CURRENT_FUNCTION  \
                          , __FILE__,__LINE__)              \
                          )                                 \
/**/

#if defined(NT2_FAILURE_AS_ERROR) && !defined(NT2_DISABLE_ERROR)
#include <nt2/sdk/errors/details/exception.hpp>
namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // warning infos type
  //////////////////////////////////////////////////////////////////////////////
  namespace details { NT2_ERROR_INFO(failure_,char const*); }

  //////////////////////////////////////////////////////////////////////////////
  // failure_exception is defined if warning are upgraded to errors
  //////////////////////////////////////////////////////////////////////////////
  struct failure_exception : virtual nt2::exception
  {
    virtual void display(std::ostream& os) const throw()
    {
      os  << " NT2 Failure: "
          << *boost::get_error_info<details::failure_>(*this) << "\n";
    }
  };
}
#endif

#endif
