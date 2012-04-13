//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_ASSERT_HPP_INCLUDED
#define NT2_SDK_ERROR_ASSERT_HPP_INCLUDED

/*!
 * \file
 * \brief Defines macros and functions controlling runtime assertions
 */

#include <nt2/sdk/error/debug.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>

#if defined(NT2_ASSERTS_AS_EXCEPTIONS) && !defined(BOOST_ENABLE_ASSERT_HANDLER)
#error BOOST_ENABLE_ASSERT_HANDLER must be defined to use NT2_ASSERTS_AS_EXCEPTIONS
#endif

#if (defined(NT2_ASSERTS_AS_EXCEPTIONS) && !defined(NT2_NO_EXCEPTIONS)) \
    || defined(DOXYGEN_ONLY)
#include <iosfwd>
#include <sstream>
#include <nt2/sdk/error/error.hpp>
#include <boost/throw_exception.hpp>

namespace nt2
{
  /**
  * @brief Runtime assertion exception
  *
  * assert_exception is thrown when a runtime assertion triggers while the
  * preprocessor symbol NT2_ASSERTS_AS_EXCEPTIONS is defined.
  *
  * @usage
  * @include assert_exception.cpp
  **/
  struct assert_exception : nt2::exception
  {
    /**
    * Builds an assert_exception from the actual runtime assertion message
    **/
    assert_exception(std::string const& msg) : nt2::exception(msg) {}
  };
}
#endif

// Debug mode has SIGTRAP to the assertion
#if defined(NT2_DEBUG) && !defined(NT2_ASSERTS_AS_EXCEPTIONS)                  \
 && defined(BOOST_ENABLE_ASSERT_HANDLER)
#include <nt2/sdk/error/trap.hpp>
#endif

// Include assert and forward the macro
#include <boost/assert.hpp>

#if defined(BOOST_ENABLE_ASSERT_HANDLER)
#if defined(NT2_DEBUG)
#include <cstdio>
#endif

namespace boost
{
  // INTERNAL ONLY
  // Define a BOOST_ASSERT handler for the NT2_ASSERTS_AS_EXCEPTIONS mode.
  extern inline
  void assertion_failed(char const* expr, char const* fn, char const* f, long l)
  {
    #if defined(NT2_ASSERTS_AS_EXCEPTIONS) && !defined(NT2_NO_EXCEPTIONS)
    std::ostringstream ss;
    ss << f << ':' << l << ": " << fn << ": Assertion " << expr << " failed.";
    #ifndef BOOST_EXCEPTION_DISABLE
    ::boost::exception_detail
    ::throw_exception_(   ::nt2::assert_exception(ss.str())
                        , fn,f,l
                      );
    #else
    ::boost::throw_exception(   ::nt2::assert_exception(ss.str())
                            );
    #endif
    #elif defined(NT2_DEBUG)
    fprintf(stderr,"%s:%d: %s: Assertion %s failed.\n",f,l,fn,expr);
    ::nt2::trap();
    #else
    boost::dispatch::ignore_unused(expr);
    boost::dispatch::ignore_unused(fn);
    boost::dispatch::ignore_unused(f);
    boost::dispatch::ignore_unused(l);
    #endif
  }

  // INTERNAL ONLY
  // Define a BOOST_ASSERT_MSG handler for the NT2_ASSERTS_AS_EXCEPTIONS mode.
  extern inline
  void assertion_failed_msg(char const* expr, char const* msg, char const* fn, char const* f, long l)
  {
    #if defined(NT2_ASSERTS_AS_EXCEPTIONS) && !defined(NT2_NO_EXCEPTIONS)
    std::ostringstream ss;
    ss << f << ':' << l << ": " << fn << ": Assertion " << expr << " failed.\n\t" << msg;
    #ifndef BOOST_EXCEPTION_DISABLE
    ::boost::exception_detail
    ::throw_exception_(   ::nt2::assert_exception(ss.str())
                        , fn,f,l
                      );
    #else
    ::boost::throw_exception(   ::nt2::assert_exception(ss.str())
                            );
    #endif
#elif defined(NT2_DEBUG)
    fprintf(stderr,"%s:%d: %s: Assertion %s failed.\n\t%s",f,l,fn,expr,msg);
    ::nt2::trap();
#else
    boost::dispatch::ignore_unused(expr);
    boost::dispatch::ignore_unused(fn);
    boost::dispatch::ignore_unused(f);
    boost::dispatch::ignore_unused(l);
    boost::dispatch::ignore_unused(msg);
#endif
  }
}

#endif

#endif
