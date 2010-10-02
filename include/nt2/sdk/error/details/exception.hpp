//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_ERROR_DETAILS_EXCEPTION_HPP_INCLUDED
#define NT2_SDK_ERROR_DETAILS_EXCEPTION_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Exception interface with std::exception and boost::exception
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/details/timestamp.hpp>

////////////////////////////////////////////////////////////////////////////////
// If exceptions are enabled, we use standard stream to build up the exception
// diagnostic and Boost.Exception for the exception handling
////////////////////////////////////////////////////////////////////////////////
#include <iosfwd>
#include <sstream>
#include <boost/exception/all.hpp>

////////////////////////////////////////////////////////////////////////////////
// Define a new NT2 exception informations diagnostic holder
////////////////////////////////////////////////////////////////////////////////
#define NT2_ERROR_INFO(NAME,TYPE)                                     \
typedef boost::error_info<struct BOOST_PP_CAT(tag_,NAME),TYPE>  NAME  \

namespace nt2
{
  struct exception;
  inline std::ostream& operator<<( std::ostream& os, exception const& e );

  //////////////////////////////////////////////////////////////////////////////
  // Exception base class
  //////////////////////////////////////////////////////////////////////////////
  struct exception : virtual boost::exception, virtual std::exception
  {
    virtual const char* what() const throw()
    {
      std::ostringstream msg;
      msg << *this;
      return msg.str().c_str();
    }

    virtual void display(std::ostream& os) const throw() =0;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Exception stream insertion operator
  // Displays basic infos then jump into the virtual display method.
  //////////////////////////////////////////////////////////////////////////////
  inline std::ostream& operator<<( std::ostream& os, exception const& e )
  {
    os
    << "****************************** NT2 ERROR *******************************\n"
    << "Raised: " << sys::timestamp().c_str()                         << "\n"
    << "File  : " << *boost::get_error_info<boost::throw_file>(e)     << "\n"
    << "Line  : " << *boost::get_error_info<boost::throw_line>(e)     << "\n"
    << "In    : " << *boost::get_error_info<boost::throw_function>(e) << "\n"
    << "************************************************************************\n";
    e.display(os);
    os
    << "************************************************************************\n";
    return os;
  }
}

#endif
