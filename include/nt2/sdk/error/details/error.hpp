//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_ERROR_DETAILS_ERROR_HPP_INCLUDED
#define NT2_SDK_ERROR_DETAILS_ERROR_HPP_INCLUDED

#include <exception>

////////////////////////////////////////////////////////////////////////////////
// When exception are disabled via -fno-exceptions, one can specify how to
// handle exception all together
////////////////////////////////////////////////////////////////////////////////
#if defined(BOOST_NO_EXCEPTIONS)
namespace boost
{
  void throw_exception( std::exception const & e )
  {
    #if defined(NT2_CUSTOM_ERROR)
    nt2::ext::throw_exception(e);
    #endif
  }
}
#endif

#endif
