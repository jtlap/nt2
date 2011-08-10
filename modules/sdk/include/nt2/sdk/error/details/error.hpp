//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_DETAILS_ERROR_HPP_INCLUDED
#define NT2_SDK_ERROR_DETAILS_ERROR_HPP_INCLUDED

#include <exception>

//==============================================================================
// When exception are disabled via -fno-exceptions, one can specify how to
// handle exception all together
//==============================================================================
#if defined(NT2_NO_EXCEPTIONS)
namespace boost
{
  inline void throw_exception( std::exception const & e )
  {
    #if defined(NT2_CUSTOM_ERROR)
    boost::dispatch::ext::throw_exception(e);
    #endif
  }
}
#endif

#endif
