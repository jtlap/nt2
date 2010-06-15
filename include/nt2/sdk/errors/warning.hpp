/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_NT2_SDK_ERRORS_WARNING_HPP_INCLUDED
#define NT2_NT2_SDK_ERRORS_WARNING_HPP_INCLUDED

#include <nt2/sdk/errors/details/warning.hpp>

////////////////////////////////////////////////////////////////////////////////
// Warning can be requalified as FATAL
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_WARNING_AS_FATAL)

#if defined(NT2_VERBOSE)
#warning NT2 Warning requalified as fatal errors
#endif

////////////////////////////////////////////////////////////////////////////////
// We force the usage of boost assert here
////////////////////////////////////////////////////////////////////////////////
#define BOOST_ENABLE_ASSERT_HANDLER
#undef  BOOST_DISABLE_ASSERTS
#include <stdio.h>
#include <stdlib.h>
#include <boost/assert.hpp>

namespace boost
{
  void assertion_failed(char const* x, char const * fn, char const * f, long l)
  {
    fprintf(stderr,"%s\n", nt2::details::warning(x,fn,f,l).c_str());
    abort();
  }
}

#define NT2_WARNING(Message)  BOOST_ASSERT( !Message )

////////////////////////////////////////////////////////////////////////////////
// Warning can be requalified as ERROR
////////////////////////////////////////////////////////////////////////////////
#elif defined(NT2_WARNING_AS_ERROR)  && !defined(NT2_NO_EXCEPTIONS)

#if defined(NT2_VERBOSE)
#warning NT2 Warning requalified as regular errors
#endif

#define NT2_WARNING(Message)                                    \
BOOST_THROW_EXCEPTION ( nt2::warning_exception()                \
                          << nt2::details::warning_( Message )  \
                      )                                         \
/**/

////////////////////////////////////////////////////////////////////////////////
// Regular active warning
////////////////////////////////////////////////////////////////////////////////
#elif !defined(NT2_DISABLE_WARNING)

#if defined(NT2_VERBOSE)
#warning NT2 Warning activated
#endif

#include <boost/current_function.hpp>

#define NT2_WARNING(Message)                                                \
nt2::details::emit_warning(                                                 \
  nt2::details::warning(Message,BOOST_CURRENT_FUNCTION,__FILE__,__LINE__))  \
/**/

////////////////////////////////////////////////////////////////////////////////
// Inactive warning do nope
////////////////////////////////////////////////////////////////////////////////
#else

#if defined(NT2_VERBOSE)
#warning NT2 Warning deactivated
#endif

#define NT2_WARNING(Message)

#endif

#endif
