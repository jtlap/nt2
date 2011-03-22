//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_ERROR_DETAILS_WARNING_HPP_INCLUDED
#define NT2_SDK_ERROR_DETAILS_WARNING_HPP_INCLUDED

#include <iostream>
#include <nt2/sdk/error/details/message.hpp>

#define NT2_EMIT_WARNING(MSG)                           \
nt2::details::emit_warning(                             \
  nt2::details::message ( "NT2 WARNING"                 \
                        , MSG , BOOST_CURRENT_FUNCTION  \
                        , __FILE__, __LINE__            \
                        ) )                             \
/**/

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Forward a warning string to the proper default or user-defined logger
  //////////////////////////////////////////////////////////////////////////////
  template<class T> inline void emit_warning( T const& msg )
  {
    #if !defined(NT2_WARNING_HANDLER)
    std::cerr << msg << "\n";
    #else
    nt2::ext::emit_warning(msg);
    #endif
  }
} }

#if defined(NT2_WARNING_AS_ERROR) && !defined(NT2_DISABLE_ERROR)
#include <nt2/sdk/error/details/exception.hpp>
namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // warning infos type
  //////////////////////////////////////////////////////////////////////////////
  namespace details { NT2_ERROR_INFO(warning_,char const*); }

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

#endif
