/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_ERRORS_ASSERT_HPP_INCLUDED
#define NT2_SDK_ERRORS_ASSERT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Runtime assertion macros and functions definitions.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// NT2_ASSERT_AS_EXCEPTION turn assertion failure into exception unless
// user already defined its own handler by defining BOOST_ENABLE_ASSERT_HANDLER
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_ASSERT_AS_EXCEPTION) && !defined(BOOST_ENABLE_ASSERT_HANDLER)
#define BOOST_ENABLE_ASSERT_HANDLER
#define NT2_FORCE_ASSERT_HANDLER
#endif

////////////////////////////////////////////////////////////////////////////////
// Include Boost.Assert only if needed
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_USE_ASSERT)
  #include <boost/assert.hpp>
#endif

////////////////////////////////////////////////////////////////////////////////
// If we're given the permission, define a assertion_failed function so that
// all assertion failure are turned into exceptions.
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_ASSERT_AS_EXCEPTION) && defined(NT2_FORCE_ASSERT_HANDLER)
#include <nt2/sdk/exceptions/throw.hpp>
#include <nt2/sdk/exceptions/tags.hpp>
#include <nt2/sdk/exceptions/assertion.hpp>

namespace boost
{
  void assertion_failed(char const* x, char const* fn, char const* f, long l)
  {
        boost::throw_exception(   boost::enable_error_info(nt2::assertion_failed())
                              <<  boost::throw_function(fn)
                              <<  boost::throw_file(f)
                              <<  boost::throw_line(l)
                              <<  nt2::details::expr_id(x)
                              );
  }
}
#endif

////////////////////////////////////////////////////////////////////////////////
// Finally override BOOST_xxxx with similar NT2_xxxx
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_USE_ASSERT)
  #define NT2_ASSERT(EXPR)  BOOST_ASSERT( EXPR )
  #define NT2_VERIFY(EXPR)  BOOST_VERIFY( EXPR )
#elif !defined(NT2_USE_ASSERT)
  #define NT2_ASSERT(EXPR)
  #define NT2_VERIFY(EXPR)  ((void)(EXPR))
#endif

#endif
