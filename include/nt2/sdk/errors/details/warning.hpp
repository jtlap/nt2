/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_NT2_SDK_ERRORS_DETAILS_WARNING_HPP_INCLUDED
#define NT2_NT2_SDK_ERRORS_DETAILS_WARNING_HPP_INCLUDED

#include <nt2/sdk/sys/string.hpp>
#include <nt2/sdk/sys/timestamp.hpp>

#if !defined(NT2_NO_EXCEPTIONS)
#include <nt2/sdk/errors/exception.hpp>

namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // warning infos type
  //////////////////////////////////////////////////////////////////////////////
  namespace details
  {
    typedef boost::error_info<struct tag_warning_,char const*>  warning_;
  }

  //////////////////////////////////////////////////////////////////////////////
  // warning_exception is defined if warning are upgraded to errors
  //////////////////////////////////////////////////////////////////////////////
  struct warning_exception : virtual nt2::exception
  {
    virtual void display(std::ostream& os) const throw()
    {
      os  << " NT2 Warning: "
          << *boost::get_error_info<details::warning_>(*this) << "\n";
    }
  };
}
#endif

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Build a warning string from warning/assertion info
  //////////////////////////////////////////////////////////////////////////////
  sys::string warning ( const char* msg, const char* fn
                      , const char* file, int line
                      )
  {
    return sys::string( "[%s] NT2 Warning in file %s:%d, function %s: %s"
                      , sys::timestamp().c_str()
                      , file, line, fn, msg
                      );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Forward a warning string to the proper default or user-defined logger
  //////////////////////////////////////////////////////////////////////////////
  void emit_warning( sys::string const& msg )
  {
    #if !defined(NT2_WARNING_HANDLER)
    fprintf(stderr,"%s\n",msg.c_str());
    #else
    nt2::ext::emit_warning(msg);
    #endif
  }
} }

#endif
